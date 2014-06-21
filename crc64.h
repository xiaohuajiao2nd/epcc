#ifndef _CRC64_H
#define _CRC64_H

#include "types.h"

void init_crc64_table();
uint64_t crc64(unsigned char* buf, uint64_t len);

#endif
