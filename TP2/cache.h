#ifndef CACHE_H_
#define CACHE_H_

#define MAIN_MEMORY_SIZE 65536
#define CACHE_SIZE 4096
#define BLOCK_SIZE 128

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