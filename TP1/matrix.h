#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>

unsigned int vecinos(unsigned char *table, unsigned int i, unsigned int j, unsigned int M, unsigned int N);

typedef struct {
    unsigned char *table;
    unsigned int state;
    unsigned int rows;
    unsigned int cols;
} matrix_t;

matrix_t *matrix_create(char *filename, unsigned int rows, unsigned int cols);
void matrix_update(matrix_t *self);
bool matrix_save(matrix_t *self, char *prefix);
void matrix_destroy(matrix_t *self);
void matrix_print(matrix_t *self, FILE *steam);

#endif // MATRIX_H
