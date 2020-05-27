#include "matrix.h"
#include <stdlib.h>

#define iterate_rows for (int i = 0; i < rows; i++)
#define iterate_cols for (int j = 0; j < cols; j++)


#ifndef USE_MIPS

unsigned int vecinos(unsigned char *table, unsigned int i, 
    unsigned int j, unsigned int M, unsigned int N) {
    int n = 0;
    if (table[((i - 1 + M) % M) * M + ((j - 1 + N) % N)] == '1') n++;
    if (table[((i - 1 + M) % M) * M + j] == '1') n++;
    if (table[((i - 1 + M) % M) * M + ((j + 1) % N)] == '1') n++;
    if (table[i * M + ((j - 1 + N) % N)] == '1') n++;
    if (table[i * M + ((j + 1) % N)] == '1') n++;
    if (table[((i + 1) % M) * M + ((j - 1 + N) % N)] == '1') n++;
    if (table[((i + 1) % M) * M + j] == '1') n++;
    if (table[((i + 1) % M) * M + ((j + 1) % N)] == '1') n++;
    return n;
}

#endif

void table_turn_on(unsigned char *self, int i, int j, int rows) {
    self[i * rows + j] = '1';
}
void table_turn_off(unsigned char *self, int i, int j, int rows) {
    self[i * rows + j] = '0';
}

void table_destroy(unsigned char *self, int rows) {
    free(self);
}

unsigned char *table_create(int rows, int cols) {
    unsigned char *mat = malloc(rows * cols * sizeof(unsigned char));
    return mat;
}

void matrix_print(matrix_t *self, FILE *stream) {
    int rows = self->rows, cols = self->cols;
    iterate_rows {
        iterate_cols {
            int offset = i * rows + j;
            int cell_value = self->table[offset] ? self->table[offset] - '0' : 0;
            fprintf(stream, "%d ", cell_value);
        }
        fprintf(stream, "\n");
    }
}

matrix_t *matrix_create(char *filename, unsigned int rows, unsigned int cols) {
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
        table_turn_on(matrix->table, i, j, rows);
    }
    fclose(file_matrix);

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->state = 0;
    return matrix;
}

void matrix_update(matrix_t *self) {
    unsigned char *new_table = table_create(self->rows, self->cols);
    int rows = self->rows, cols = self->cols, offset;

    iterate_rows {
        iterate_cols {
            offset = i * rows + j;
            new_table[offset] = self->table[offset];
            unsigned int n_vecinos = vecinos(self->table, i, j, self->rows, self->cols);
            if ((self->table[offset] == '1') && (n_vecinos < 2 || n_vecinos > 3))
                table_turn_off(new_table, i, j, rows);
            else if ((!self->table[offset] || (self->table[offset] == '0')) && n_vecinos == 3)
                table_turn_on(new_table, i, j, rows);
        }
    }
    table_destroy(self->table, self->rows);
    self->table = new_table;
    self->state++;
}

bool matrix_save(matrix_t *self, char *prefix) {
    char fname[256];
    sprintf(fname, "%s_%03d.pbm", prefix, self->state);
    FILE *f;
    if (!(f = fopen(fname, "w"))) return false;
    fprintf(f, "P1\n");
    fprintf(f, "%ud %ud\n", self->cols, self->rows);
    matrix_print(self, f);
    fclose(f);
    return true;
}

void matrix_destroy(matrix_t *self) {
    table_destroy(self->table, self->rows);
    free(self);
}
