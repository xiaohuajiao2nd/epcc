#include "crc64.h"
#include <stdio.h>
#include <string.h>
#include <mpi.h>
#include <omp.h>
#include <time.h>
#include "hash_table.h"
#include "types.h"
#include "crack.h"


//#define HMPI


uint64_t DST_VALUE;
int INPUT_LEN;
int HALF_INPUT_LEN;

int64_t BYTES_SUM; 

#ifndef HMPI
void crack_range(int64_t *start, int64_t *end)
{
    *start = '0' * HALF_INPUT_LEN;
    *end = BYTES_SUM - ('0' * (INPUT_LEN - HALF_INPUT_LEN));
    //printf("%lld, %lld\n", *start, *end);
}
#endif

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
	sscanf(argv[1], "%llx", &DST_VALUE);
	sscanf(argv[2], "%d", &BYTES_SUM);
	sscanf(argv[3], "%d", &INPUT_LEN);

	HALF_INPUT_LEN = INPUT_LEN / 2;
	//printf("dst_value: %llx\n", DST_VALUE);
}

int main(int argc, char *argv[])
{
	int num;
	int id = -1;
	int64_t crack_start, crack_end;
	double time_start, time_end;

	if (argc < 4)
	{
		return 0;	
	}
	update_constant(argv);
	
//	printf("ID1: %d\n", id);

#ifdef HMPI
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &num);
	time_start = MPI_Wtime();
	crack_range(id, num, &crack_start, &crack_end);
	printf("Define HMPI\n");

#else

#ifdef HOMP
	printf("Define HOMP\n");
	time_start = omp_get_wtime();
#else
	printf("No def\n");
	time_start = time(NULL);
#endif
	crack_range(&crack_start, &crack_end);
#endif
	
	//printf("ID2: %d\n", id);
	crack(id, crack_start, crack_end);

	fflush(stdout);
#ifdef HMPI
	time_end = MPI_Wtime();
	MPI_Finalize();
#else
#ifdef HOMP
	time_end = omp_get_wtime();
#else
	time_end = time(NULL);
#endif
#endif

	printf("[Node %d ]Time: %lf\n", id, time_end - time_start);
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

