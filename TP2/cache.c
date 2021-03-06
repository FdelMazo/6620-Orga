#include "cache.h"
#include <stdio.h>
#include <string.h>

unsigned int _get_tag(unsigned int address);
void _update_cache_count(bool data_is_in_cache);
unsigned int _get_block(unsigned int address);
unsigned char _read_from_cache(unsigned int set, unsigned int way,
                               unsigned int offset);
void _update_blocks_counter_from_set(unsigned int set);

main_memory_t main_memory;
cache_t cache;

void init() {
    printf("INIT \n");
    memset(main_memory.data, 0, MAIN_MEMORY_SIZE);

    memset(cache.blocks, INVALID, sizeof(cache.blocks));
    cache.miss_count = 0;
    cache.hit_count = 0;
}

unsigned int get_offset(unsigned int address) { return address % BLOCK_SIZE; }

unsigned int find_set(unsigned int address) {
    return address / BLOCK_SIZE % CACHE_SETS;
}

unsigned int select_oldest(unsigned int setnum) {
    cache_block_t *blocks_in_set = cache.blocks[setnum];
    unsigned int oldest = 0;
    for (size_t i = 1; i < N_WAYS; i++) {
        if (blocks_in_set[oldest].counter < blocks_in_set[i].counter) {
            oldest = i;
        }
    }
    return oldest;
}

int compare_tag(unsigned int tag, unsigned int set) {
    cache_block_t *blocks_in_set = cache.blocks[set];
    cache_block_t block;
    for (int i = 0; i < N_WAYS; i++) {
        block = blocks_in_set[i];
        if (block.valid && block.tag == tag) {
            return i;
        }
    }
    return -1;
}

void read_tocache(unsigned int blocknum, unsigned int way, unsigned int set) {
    int block_starting_address = blocknum * BLOCK_SIZE;
    cache_block_t *block = &cache.blocks[set][way];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block->data[i] = main_memory.data[block_starting_address + i];
    }
    block->valid = VALID;
    block->tag = _get_tag(block_starting_address);
    block->counter = 0;
}

/* Como la cache esta implementada con Write Through y no-write allocate, si
escribimos en la cache, esto nos garantiza que el bloque correspondiente a la
direccion se encuentra en la misma. */
void write_tocache(unsigned int address, unsigned char value) {
    unsigned int tag = _get_tag(address);
    unsigned int set = find_set(address);
    unsigned int offset = get_offset(address);
    int way = compare_tag(tag, set);
    cache_block_t *block = &cache.blocks[set][way];
    block->data[offset] = value;
    block->counter = 0;
}

unsigned char read_byte(unsigned int address) {
    unsigned int tag = _get_tag(address);
    unsigned int set = find_set(address);
    int way = compare_tag(tag, set);
    unsigned char byte_read;
    bool is_in_cache = way >= 0;
    _update_blocks_counter_from_set(set);
    if (!is_in_cache) {
        unsigned int block_num = _get_block(address);
        way = select_oldest(set);
        read_tocache(block_num, way, set);
    }

    unsigned int offset = get_offset(address);
    byte_read = _read_from_cache(set, way, offset);
    _update_cache_count(is_in_cache);

    printf("READ: %d -> %u \n", address, byte_read);
    return byte_read;
}

void write_byte(unsigned int address, unsigned char value) {
    unsigned int tag = _get_tag(address);
    unsigned int set = find_set(address);
    int way = compare_tag(tag, set);
    bool is_in_cache = way >= 0;

    _update_blocks_counter_from_set(set);
    main_memory.data[address] = value;
    if (is_in_cache) {
        write_tocache(address, value);
    }
    _update_cache_count(is_in_cache);
    printf("WRITE: %d <- %u \n", address, value);
}

float get_miss_rate() {
    if (cache.miss_count == 0) return 0;
    int total_count = cache.miss_count + cache.hit_count;
    float mr = cache.miss_count / (float)total_count * 100;
    printf("MISS_RATE: %0.2f%% \n", mr);
    return mr;
}

/* Funciones auxiliares */

unsigned char _read_from_cache(unsigned int set, unsigned int way,
                               unsigned int offset) {
    cache_block_t block = cache.blocks[set][way];
    block.counter = 0;

    return block.data[offset];
}

void _update_blocks_counter_from_set(unsigned int set) {
    cache_block_t *blocks_in_set = cache.blocks[set];
    for (size_t i = 0; i < N_WAYS; i++) {
        blocks_in_set[i].counter += 1;
    }
}

unsigned int _get_block(unsigned int address) { return address / BLOCK_SIZE; }

unsigned int _get_tag(unsigned int address) {
    unsigned int int_for_set_and_offset = pow(2, INDEX_SIZE + OFFSET_SIZE);
    return address / int_for_set_and_offset;
}

void _update_cache_count(bool data_is_in_cache) {
    if (data_is_in_cache) {
        cache.hit_count += 1;
    } else {
        cache.miss_count += 1;
    }
}
