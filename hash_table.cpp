#include "hash_table.h"

Node **crc_list;
//#pragma omp threadprivate(crc_list)

int HASH_TABLE_SIZE = 1 << 27;
int MASK = HASH_TABLE_SIZE - 1;

