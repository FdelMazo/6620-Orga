#include "cache.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAIN_MEMORY_SIZE 65536
#define CACHE_SIZE 4096
#define BLOCK_SIZE 128
#define CACHE_SETS 8
#define N_WAYS 4

#define BLOCKS_COUNT (CACHE_SIZE / NO_WAYS / BLOCK_SIZE)
#define ADDRESS_SIZE 16
#define OFFSET_SIZE (log(BLOCK_SIZE) / log(2))
#define INDEX_SIZE (log(BLOCKS_COUNT) / log(2))
#define TAG_SIZE (ADDRESS_SIZE - INDEX_SIZE - OFFSET_SIZE)

typedef struct
{
    unsigned char data[MAIN_MEMORY_SIZE];
} main_memory_t;

typedef struct
{
    unsigned char tag;
    bool valid;
    bool dirty;
    unsigned char data[BLOCK_SIZE];
} cache_block_t;
typedef struct
{
    cache_block_t blocks[CACHE_SETS][N_WAYS];
    int miss_count;
    int hit_count;
} cache_t;

main_memory_t main_memory;
cache_t cache;

void init()
{
    printf("Executing init()\n");
    memset(main_memory.data, 0, MAIN_MEMORY_SIZE);

    memset(cache.blocks, 0, sizeof(cache.blocks));
    cache.miss_count = 0;
    cache.hit_count = 0;
}

unsigned int get_offset(unsigned int address)
{
    return address % BLOCK_SIZE;
}

unsigned int find_set(unsigned int address)
{
    return address / BLOCK_SIZE % CACHE_SETS;
}

unsigned char read_byte(unsigned int address)
{
    printf("Executing read_byte\n");
    return '0';
}

void write_byte(unsigned int address, unsigned char value)
{
    printf("Executing write_byte\n");
}

float get_miss_rate()
{
    printf("Getting miss rate\n");
    return 0;
}
