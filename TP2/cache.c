#include "cache.h"
#include <string.h>
#include <stdio.h>

void init()
{
    printf("Executing init()\n");
}

float get_miss_rate()
{
    printf("Getting miss rate\n");
    return 0;
}

void write_byte(unsigned int address, unsigned char value)
{
    printf("Executing write_byte\n");
}

unsigned char read_byte(unsigned int address)
{
    printf("Executing read_byte\n");
    return '0';
}