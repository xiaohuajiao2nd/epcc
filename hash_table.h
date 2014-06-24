#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <stdio.h>
#include <string.h>
#include <omp.h>
#include "types.h"


extern int HALF_INPUT_LEN;

/**************************
 * Hash table
 * ***********************/

typedef struct _Node
{
    uint64_t value;
    unsigned char str[16];
    struct _Node * next;
} Node;

extern Node **crc_list;
#pragma omp threadprivate(crc_list)

extern int HASH_TABLE_SIZE;
extern int MASK;


inline uint64_t count_element()
{
    uint64_t count = 0;
    for (uint64_t i = 0; i < HASH_TABLE_SIZE; i++)
    {
        if (crc_list[i])
        {
            Node *p = crc_list[i];
            while (p)
            {
                count++;
                p = p->next;
            }
        }
    }
    return count;
}

inline void add_element(uint64_t e, unsigned char *buf)
{
    uint64_t index = e & MASK;
    Node *p = crc_list[index];
//    int tid = omp_get_thread_num();

    if (!p)
    {
        //printf("Thread %d: insert new: %llx  index: %llx\n", tid, e, index);
        crc_list[index] = new Node;
        crc_list[index]->value = e;
        crc_list[index]->next = NULL;

        memcpy(crc_list[index]->str, buf, HALF_INPUT_LEN);
    }
    else
    {
        //printf("Thread %d: index exists: %llx\n", tid, index);
        while (p->next)
            p = p->next;
        p->next = new Node;
        p->next->value = e;
        p->next->next = NULL;

        memcpy(p->next->str, buf, HALF_INPUT_LEN);
    }
}

inline uint64_t check_value(uint64_t e)
{
    uint64_t index = e & MASK;
//    printf("index: %llx\n", index);
    if (crc_list[index])
    {
        Node *p = crc_list[index];
        while (p != NULL && p->value != e)
        {
//            printf("Checking %llx\n", e);
            p = p->next;
        }
        if (p)
            return index;
        return -1;
    }
    //printf("not found\n");
    return -1;
}

inline void search_key_by_index(uint64_t index, uint64_t goal, unsigned char *buf)
{
    Node *p = crc_list[index];
    while (p != NULL && p->value != goal)
    {
        p = p->next;
    }
    if (p)
    {
        memcpy(buf, p->str, HALF_INPUT_LEN);
    }
}

inline void delete_element(Node *node)
{
    if (node)
    {
        delete_element(node->next);
        delete node;
    }
}

inline void clear()
{
    int i;
    for (i = 0; i < HASH_TABLE_SIZE; i++)
    {
        delete_element(crc_list[i]);
        crc_list[i] = NULL;
    }
}

#endif
