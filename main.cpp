#include "crc64.h"
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include "hash_table.h"
#include "types.h"
#include "crack.h"




uint64_t DST_VALUE = 0x15ad90b88aba1847;
int INPUT_LEN = 6;
int HALF_INPUT_LEN = INPUT_LEN / 2;

int64_t BYTES_SUM; 

void crack_range(int64_t *start, int64_t *end)
{
/*
    *start = dict[0] * HALF_INPUT_LEN;
    *end = BYTES_SUM - (dict[0] * (INPUT_LEN - HALF_INPUT_LEN));
    printf("%lld, %lld\n", *start, *end);
*/
}

/*
void update_constant(unsigned char *buf)
{
    INPUT_LEN = strlen((char *)buf);
    HALF_INPUT_LEN = INPUT_LEN / 2;

    BYTES_SUM = 0;
    for (size_t i = 0; i < INPUT_LEN; i++)
    {
        BYTES_SUM += buf[i];
    }
}
*/

void update_constant(char *argv[])
{
	sscanf(argv[1], "%d", &DST_VALUE);
	sscanf(argv[2], "%d", &INPUT_LEN);
}

int main(int argc, char *argv[])
{
	int id, num;
	int64_t crack_start, crack_end;

	if (argc < 3)
	{
		return 0;	
	}
	update_constant(argv);
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &num);
	
	crack(0, 291);

	printf("Node %d is done\n", id);
	fflush(stdout);
	MPI_Finalize();
	return 0;
}

void hash_table_test()
{
    /*
    for (int i = 0; i < 64; i++)
    {
        add_element(1LL << i);
    }
    add_element(0x1111111111111111);
    add_element(0x2222222222222222);
    add_element(0x2223222222222222);
    add_element(0x2223222222222322);
    add_element(0x2223222222222232);
    add_element(0x2223222222222223);
    */

//    printf("hash table size: %llu\n", count_element());
    /*
    printf("MASK: %llx\n", MASK);
    for (int i = 0; i < 10; i++)
    {
        if (check_value(1LL << i))
            printf("success %llx\n", 1LL << i);
        else
            printf("fail %llx\n", 1LL << i);
    }
    */
}

