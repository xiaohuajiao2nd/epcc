#include <string.h>
#include <omp.h>

#include "crack.h"
#include "hash_table.h"
#include "crc64.h"


int RET_SUM_OUT = -1;
int RET_NO_FOUND = 0;
int RET_FOUND = 1;

const int DICT_SIZE = 62;
unsigned char dict[63] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

uint64_t lookup_table[256] = {0};

unsigned char key[14];
#pragma omp threadprivate(key)

extern uint64_t DST_VALUE;
extern uint64_t HALF_DEPTH;
extern int INPUT_LEN;
extern int HALF_INPUT_LEN;
extern int64_t BYTES_SUM;

/***************************
 * Brute force by dfs
 * ************************/

extern uint64_t crc64_table[256];

void init_lookup_table()
{
    for (int i = 0; i < 256; i++)
    {
        lookup_table[(crc64_table[i] >> 56) & 0xff] = i;//crc64_table[i];
    }
}

inline uint64_t alg(uint64_t value, char ch)
{
    return (value >> 8) ^ (crc64_table[ch ^ (value & 0xff)]);
}

inline uint64_t reverse_alg(uint64_t value, char ch)
{
    int index = lookup_table[(value >> 56) & 0xff];
    //printf("lookup: %02x - (%016llx, %016llx) -> %016llx\n", index, crc64_table[index], value, crc64_table[index] ^ value);

    //uint64_t tmp = value ^ lookup_table[(value >> 56) & 0xff];
    return (((value ^ crc64_table[index]) << 8) & 0xffffffffffffffff)
            | ((ch ^ index) & 0xff);
}

int forward_dfs(int depth, int64_t sum, uint64_t value)
{
    uint64_t tmp_value;
    int64_t tmp_sum;

    if (depth == HALF_INPUT_LEN)
    {
        //printf("%016llx\n", value);
        if (sum == 0)
            add_element(value, key);
        return RET_NO_FOUND;
    }

    for (int i = 0; i < DICT_SIZE; i++)
    {
        tmp_value = alg(value, dict[i]);
        tmp_sum = sum - dict[i];
        key[depth] = dict[i];

        /*
        for (int j = 0; j < depth; j++)
            printf("\t");
        printf("%c - %lld\n", dict[i], tmp_sum);
        */

        if (tmp_sum < 0)
            return RET_NO_FOUND;
        forward_dfs(depth + 1, tmp_sum, tmp_value);
    }

    return RET_NO_FOUND;
}

int reverse_dfs(int depth, int64_t sum, uint64_t value)
{
    uint64_t tmp_value;
    int64_t index;
    int64_t tmp_sum;

    if (depth == (INPUT_LEN - HALF_INPUT_LEN - 1 - (INPUT_LEN & 1)))
    {
        //printf("%016llx\n", value);
        if (sum == 0 && (index = check_value(value)) >= 0)
        {
            unsigned char buf[INPUT_LEN];
            memset(buf, 0, INPUT_LEN);
            printf("table index: %016llx\n", index);
            search_key_by_index(index, value, buf);

            printf("Get it: %s%s\n", buf, (unsigned char *)(key + HALF_INPUT_LEN));

            FILE *f = fopen("result.txt", "w");
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

        if (tmp_sum < 0)
        {
            return RET_NO_FOUND;
        }

        if (reverse_dfs(depth - 1, tmp_sum, tmp_value) == RET_FOUND)
            return RET_FOUND;
    }

    return RET_NO_FOUND;
}


void crack(int64_t start, int64_t end)
{
    int ret;
    double time_start, time_end;
    bool found = false;

    time_start = omp_get_wtime();

    init_crc64_table();
    init_lookup_table();

    omp_set_dynamic(0);

    memset(key, 0, sizeof key);

    //omp_set_num_threads(2);
    
#pragma omp parallel
    {
        crc_list = new Node*[HASH_TABLE_SIZE];
    }

#pragma omp parallel for private(ret)
    for (int64_t i = start; i <= end; i++)
    {
        printf("Search: %lld + %lld\n", i, BYTES_SUM - i);
        forward_dfs(0, i, 0);

        ret = reverse_dfs(INPUT_LEN - 1, BYTES_SUM - i, DST_VALUE);

    //    printf("hash table size: %llu\n", count_element());
        clear();
        if (ret == RET_FOUND)
            found = true;
        if (found)
            i = BYTES_SUM;
    }

    time_end = omp_get_wtime();
    printf("[Time]: %lf\n", time_end - time_start);
}
