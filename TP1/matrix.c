#include "matrix.h"
#include <stdlib.h>

#define iterate_rows for (int i = 0; i < rows; i++)
#define iterate_cols for (int j = 0; j < cols; j++)

typedef unsigned int uint;

uint vecinos(bool **table, uint i, uint j, uint M, uint N) {
    int n = 0;
    if (table[(i - 1 + M) % M][(j - 1 + N) % N]) n++;
    if (table[(i - 1 + M) % M][j]) n++;
    if (table[(i - 1 + M) % M][(j + 1) % N]) n++;
    if (table[i][(j - 1 + N) % N]) n++;
    if (table[i][(j + 1) % N]) n++;
    if (table[(i + 1) % M][(j - 1 + N) % N]) n++;
    if (table[(i + 1) % M][j]) n++;
    if (table[(i + 1) % M][(j + 1) % N]) n++;
    return n;
}

void table_turn_on(bool **self, int i, int j) { self[i][j] = true; }
void table_turn_off(bool **self, int i, int j) { self[i][j] = false; }

void table_destroy(bool **self, int rows) {
    iterate_rows { free(self[i]); }
    free(self);
}

bool **table_create(int rows, int cols) {
    bool **table = calloc(rows, sizeof(bool *));
    iterate_rows {
        table[i] = calloc(cols, sizeof(bool *));
        iterate_cols { table_turn_off(table, i, j); }
    }
    return table;
}

void matrix_print(matrix_t *self, FILE *stream) {
    int rows = self->rows, cols = self->cols;
    iterate_rows {
        iterate_cols { fprintf(stream, "%d ", self->table[i][j]); }
        fprintf(stream, "\n");
    }
}

matrix_t *matrix_create(char *filename, size_t rows, size_t cols) {
    matrix_t *matrix;
    if (!(matrix = malloc(sizeof(matrix_t)))) return NULL;

    if (!(matrix->table = table_create(rows, cols))) {
        free(matrix);
        return NULL;
    };

    FILE *file_matrix;
    if (!(file_matrix = fopen(filename, "r"))) {
        table_destroy(matrix->table, rows);
        free(matrix);
        return NULL;
    }
    int i = 0, j = 0;
    while ((fscanf(file_matrix, "%d %d\n", &i, &j)) != EOF) {
        table_turn_on(matrix->table, i, j);
    }
    fclose(file_matrix);

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->state = 0;
    return matrix;
}

void matrix_update(matrix_t *self) {
    bool **new_table = table_create(self->rows, self->cols);
    int rows = self->rows, cols = self->cols;

    iterate_rows {
        iterate_cols {
            new_table[i][j] = self->table[i][j];
            uint n_vecinos = vecinos(self->table, i, j, self->rows, self->cols);
            if (self->table[i][j] && (n_vecinos < 2 || n_vecinos > 3))
                table_turn_off(new_table, i, j);
            else if (!self->table[i][j] && n_vecinos == 3)
                table_turn_on(new_table, i, j);
        }
    }
    table_destroy(self->table, self->rows);
    self->table = new_table;
    self->state++;
}

bool matrix_save(matrix_t *self, char *prefix) {
    char fname[256];
    sprintf(fname, "%s_%03ld.pbm", prefix, self->state);
    FILE *f;
    if (!(f = fopen(fname, "w"))) return false;
    fprintf(f, "P1\n");
    fprintf(f, "%ld %ld\n", self->rows, self->cols);
    matrix_print(self, f);
    fclose(f);
    return true;
}

void matrix_destroy(matrix_t *self) {
    table_destroy(self->table, self->rows);
    free(self);
}
