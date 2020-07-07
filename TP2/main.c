#define _GNU_SOURCE
#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_commands(const char *filename);
static int read_address(char *line);
static int write_in_address(char *line);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Invalid arguments. Just call this program specifying "
                        "the file: ./main <file_name>.\n");
        return 1;
    }

    init();

    int result = read_commands(argv[1]);

    return result;
}

static int read_commands(const char *filename) {
    FILE *commands_file;
    if (!(commands_file = fopen(filename, "r"))) {
        fprintf(stderr, "Error opening filename.\n");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    int result = 0;

    while (getline(&line, &len, commands_file) != -1) {
        if (strncmp(line, "FLUSH", 5) == 0) {
            init();
        } else if (strncmp(line, "R", 1) == 0) {
            result = read_address(line);
        } else if (strncmp(line, "W", 1) == 0) {
            result = write_in_address(line);
        } else if (strncmp(line, "MR", 2) == 0) {
            get_miss_rate();
        } else {
            fprintf(stderr, "Error: invalid line.\n");
            return 1;
        }

        if (result == 1) return result;
    }
    fclose(commands_file);
    return result;
}

static int read_address(char *line) {
    unsigned int address;
    int result = sscanf(line, "R %u", &address);
    if (result != 1) {
        fprintf(stderr, "Error reading address.\n");
        return 1;
    } else if (address >= MAIN_MEMORY_SIZE) {
        fprintf(stderr, "Error: the address specified is bigger than the size "
                        "of the main memory.\n");
        return 1;
    }
    read_byte(address);
    return 0;
}

static int write_in_address(char *line) {
    unsigned int address;
    unsigned int value;
    int result = sscanf(line, "W %u, %u", &address, &value);
    if (result != 2) {
        fprintf(stderr, "Error reading address and value.\n");
        return 1;
    } else if (address >= MAIN_MEMORY_SIZE) {
        fprintf(stderr, "Error: the address specified is bigger than the size "
                        "of the main memory.\n");
        return 1;
    }
    write_byte(address, value);
    return 0;
}
