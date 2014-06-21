#include "crc64.h"
#include <stdio.h>


uint64_t CRC_CONSTANT = 0x8c997d55124358a1;

uint64_t crc64_table[256] = {0};

/***************************
 * CRC64 Algorithm
 * ************************/
void init_crc64_table()
{
    for (int i = 0; i != 256; i++)
    {
        uint64_t crc = i;
        for (int j = 0; j != 8; j++)
        {
            if(crc & 1)
            crc = (crc >> 1) ^ CRC_CONSTANT;
            else
            crc >>= 1;
        }
        crc64_table[i] = crc;
    }

    /*
    FILE* f = fopen("crc_table.txt", "w");
    for (int i = 0; i< 256; i++)
    {
        fprintf(f, "%02x: %016llx\n", i, crc64_table[i]);
    }
    fclose(f);
    */
}

uint64_t crc64(unsigned char *buf, uint64_t len)
{
	uint64_t a = 0;
	for (uint64_t i = 0; i < len; i++)
    {
		int j = buf[i] ^ (a & 0xff);
		a = (a >> 8) ^ (crc64_table[j]);
	}
	return a;
}
