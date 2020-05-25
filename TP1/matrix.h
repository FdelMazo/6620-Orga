#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>
#include <stdio.h>

typedef struct {
    char *table;
    size_t state;
    size_t rows;
    size_t cols;
} matrix_t;

matrix_t *matrix_create(char *filename, size_t rows, size_t cols);
void matrix_update(matrix_t *self);
bool matrix_save(matrix_t *self, char *prefix);
void matrix_destroy(matrix_t *self);
void matrix_print(matrix_t *self, FILE *steam);

#endif // MATRIX_H
