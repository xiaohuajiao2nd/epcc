#ifndef _CRACK_H
#define _CRACK_H

#include "types.h"

void crack(int64_t start, int64_t end);

void init_lookup_table();

int forward_dfs(int depth, int64_t sum, uint64_t value);
int reverse_dfs(int depth, int64_t  sum, uint64_t value);

#endif
