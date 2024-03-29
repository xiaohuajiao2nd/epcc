#include <string.h>

#include "crack.h"
#include "hash_table.h"
#include "crc64.h"
#include "options.h"


#ifdef HOMP
#include <omp.h>
#endif

#ifdef HMPI
#include <mpi.h>
#endif



const int RET_SUM_OUT = -1;
const int RET_NO_FOUND = 0;
const int RET_FOUND = 1;

const int RET_CONTINUE = 1;
const int RET_BREAK = 2;

const int DICT_SIZE = 62;
const unsigned char dict[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

uint64_t lookup_table[256] = {0};

unsigned char key[14];
#ifdef HOMP
#pragma omp threadprivate(key)
#endif

extern uint64_t DST_VALUE;
extern uint64_t HALF_DEPTH;
extern int INPUT_LEN;
extern int FORWARD_DST;
extern int BACKWARD_DST;
extern int64_t BYTES_SUM;

/***************************
 * Brute force by dfs
 * ************************/

extern uint64_t crc64_table[256];

/**************************
 * According to observation, we found the crc table has a property here:
 * There are 256 members in this table. The first and last byte of each member in crc table is unique,
 * so we can construct a lookup table to accelarate the BF.
 * 根据对CRC表的观察，我们发现了一个规律：
 * 表中有256个成员，
 * 且表中每个成员的首字节和尾字节都是唯一的,
 * 故可构造一个查找表来加速
 * ***********************/
void init_lookup_table()
{
    for (int i = 0; i < 256; i++)
    {
        lookup_table[(crc64_table[i] >> 56) & 0xff] = i;//crc64_table[i];
    }
}

/*************************
 * Single round for crc calculation
 * CRC的一轮运算
 * **********************/
inline uint64_t alg(uint64_t value, char ch)
{
    return (value >> 8) ^ (crc64_table[ch ^ (value & 0xff)]);
}

/*************************
 * Single round for reversed crc calculation
 * CRC一轮运算的逆运算
 * **********************/
inline uint64_t reverse_alg(uint64_t value, char ch)
{
    int index = lookup_table[(value >> 56) & 0xff];
    //printf("lookup: %02x - (%016llx, %016llx) -> %016llx\n", index, crc64_table[index], value, crc64_table[index] ^ value);

    return (((value ^ crc64_table[index]) << 8) & 0xffffffffffffffff)
            | ((ch ^ index) & 0xff);
}

inline int need_continue(int sum, int rest_depth)
{
	return (sum < 0 ||((sum - rest_depth * dict[0]) < 0)) ? RET_BREAK: RET_CONTINUE;
}

/****************************************
 * Do DFS in forward direction and stop at the half length of result string.
 * Keep the middle result in the hash table so that we can check whether the result
 * exists or not in reverse DFS.
 * 正向DFS，在结果长度一半处停止，
 * 将中间结果记入表中, 以便后续反向搜索时进行中间相遇
 * *************************************/
int forward_dfs(int depth, int64_t sum, uint64_t value)
{
    uint64_t tmp_value;
    int64_t tmp_sum;

    // Arrive the end of forward searching.
    // 到达正向搜索终点深度
    if (depth == FORWARD_DST)//HALF_INPUT_LEN)
    {
        //printf("%016llx\n", value);

        //Only when current sum is 0 can we add the middle result to table.
        //Otherwise it is not the possible result we need.
        //当且仅当当前sum的值为0时，才把中间结果记入表中
        //否则此时的sum及其所代表的前半部分crc值不是我们想要的
        if (sum == 0)
            add_element(value, key);
        return RET_NO_FOUND;
    }

    for (int i = 0; i < DICT_SIZE; i++)
    {
        tmp_value = alg(value, dict[i]);
        tmp_sum = sum - dict[i];
        key[depth] = dict[i];

        //If sum is 0 now, we need not continue the searching in this depth, just return.
        //若用于下一步的sum已经减小至0以下，则没必要把当前这一层的搜索继续下去
        //直接返回
	if (tmp_sum < 0 ||((tmp_sum - (FORWARD_DST - depth - 1) * dict[0]) < 0))
		return RET_NO_FOUND;

        //Continue to deeper search.
        //深度+1，sum减去当前枚举的值，继续往下一层搜索
        forward_dfs(depth + 1, tmp_sum, tmp_value);
    }

    return RET_NO_FOUND;
}

/****************************************
 * Do DFS in backward direction and stop at the point of forward DFS stopped.
 * Find the result in hash table. If found, we get the result,
 * otherwise try another byte.
 * 反向DFS，在正向DFS停止的点停止即可，
 * 查看表中是否存在当前计算出来的这个中间值，
 * 若存在，则说明找到了正确的结果，将正确的结果写入文件中并直接返回
 * 若未找到，则继续搜索
 * *************************************/
int reverse_dfs(int depth, int64_t sum, uint64_t value)
{
    uint64_t tmp_value;
    int64_t index;
    int64_t tmp_sum;

    if (depth == BACKWARD_DST)//(INPUT_LEN - HALF_INPUT_LEN - 1 - (INPUT_LEN & 1)))
    {
        //printf("%016llx\n", value);
        if (sum == 0 && (index = check_value(value)) >= 0)
        {
            unsigned char buf[INPUT_LEN];
            memset(buf, 0, INPUT_LEN);
        //    printf("table index: %016llx\n", index);
            search_key_by_index(index, value, buf);

            printf("Get it: %s%s\n", buf, (unsigned char *)(key + HALF_INPUT_LEN));

            FILE *f = fopen("result.txt", "a");
            fprintf(f, "Get it: %s%s\n", buf, (unsigned char *)(key + HALF_INPUT_LEN));
            fclose(f);
            //printf("%s", buf);
            //printf("%s\n", key[HALF_INPUT_LEN]);
            return RET_FOUND;
        }
        return RET_NO_FOUND;
    }

    for (int i = 0; i < DICT_SIZE; i++)
    {
        tmp_value = reverse_alg(value, dict[i]);
        tmp_sum = sum - dict[i];
        key[depth] = dict[i];

        /*
        for (int j = 0; j < INPUT_LEN - depth - 1; j++)
            printf("\t");
        printf("%c ", dict[i]);
        printf("- %016llx\n", tmp_value);
        */

	if (tmp_sum < 0 ||((tmp_sum - (depth - BACKWARD_DST - 1) * dict[0]) < 0))
		return RET_NO_FOUND;

        if (reverse_dfs(depth - 1, tmp_sum, tmp_value) == RET_FOUND)
            return RET_FOUND;
    }

    return RET_NO_FOUND;
}


void crack_range(int id, int node_num, int64_t *start, int64_t *end)
{
	int64_t global_range_start, global_range_end;
	global_range_start = dict[0] * HALF_INPUT_LEN;
	global_range_end = BYTES_SUM - (dict[0] * (INPUT_LEN - HALF_INPUT_LEN));

	//printf("%lld %lld len:%d half_len:%d\n", global_range_start, global_range_end, INPUT_LEN, HALF_INPUT_LEN);
	*start = (id * (global_range_end - global_range_start + 1)) / node_num + global_range_start;
	*end = ((id + 1) * (global_range_end - global_range_start + 1)) / node_num - 1 + global_range_start;

	//printf("Node:%d\tstart:%lld end:%lld\n", id, *start, *end);
}


void crack(int id, int64_t start, int64_t end)
{
    int ret;
    bool found = false;
	int64_t i;

    init_crc64_table();
    init_lookup_table();


    memset(key, 0, sizeof key);

//    omp_set_num_threads(omp_get_num_procs() * 2);
    
	//printf("[Node %d start-end] %lld ~ %lld\n", id, start, end);
#ifdef HOMP
    omp_set_dynamic(0);
#pragma omp parallel
#endif
    {
        crc_list = new Node*[HASH_TABLE_SIZE];
    }

#ifdef HOMP
#pragma omp parallel for private(i, ret)
#endif
    for (i = start; i <= end; i++)
    {
 //       printf("Search: %lld + %lld\n", i, BYTES_SUM - i);
	fflush(stdout);
        forward_dfs(0, i, 0);

        ret = reverse_dfs(INPUT_LEN - 1, BYTES_SUM - i, DST_VALUE);

//        clear();
        if (ret == RET_FOUND)
	{
            found = true;
#ifdef HMPI
		MPI_Bcast(&found, 1, MPI_CHAR, id, MPI_COMM_WORLD);
#endif
	    //printf("[Node %d endindex]: %lld/%lld\n", id, i, end);
	}
	if (found)
		i = BYTES_SUM;
    }

    /*
#ifdef HOMP
#pragma omp parallel
#endif
    {
        clear();
    }
    */
}

