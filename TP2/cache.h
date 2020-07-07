#ifndef CACHE_H_
#define CACHE_H_

#include <math.h>

#define MAIN_MEMORY_SIZE (64 * 1024) // 64 Kilobytes
#define CACHE_SIZE (4 * 1024)
#define BLOCK_SIZE 128
#define CACHE_SETS 8
#define N_WAYS 4
#define INVALID_BLOCK 0

#define BLOCKS_COUNT (CACHE_SIZE / N_WAYS / BLOCK_SIZE)
#define ADDRESS_SIZE 16
#define OFFSET_SIZE (log(BLOCK_SIZE) / log(2))
#define INDEX_SIZE (log(CACHE_SETS) / log(2))
#define TAG_SIZE (ADDRESS_SIZE - INDEX_SIZE - OFFSET_SIZE)

void init();
unsigned int get_offset(unsigned int address);
unsigned int find_set(unsigned int address);
unsigned int select_oldest(unsigned int setnum);
int compare_tag(unsigned int tag, unsigned int set);
void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set);
void write_tocache(unsigned int address, unsigned char value);
unsigned char read_byte(unsigned int address);
void write_byte(unsigned int address, unsigned char value);
float get_miss_rate();

#endif
