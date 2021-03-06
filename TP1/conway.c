#include "matrix.h"
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ESC 27
#define help_message                                                           \
    "Uso:\n  conway -h\n  conway -V\n  conway i M N inputfile [-o "            \
    "outputprefix] [-p]\n"                                                     \
    "Opciones:\n"                                                              \
    "  -h, --help     Imprime este mensaje.\n"                                 \
    "  -V, --version  Da la versión del programa.\n"                          \
    "  -o             Prefijo de los archivos de salida.\n"                    \
    "  -p             Muestra los estados por terminal.\n"                     \
    "Ejemplos:\n"                                                              \
    "  conway 10 20 20 glider -o estado\n"                                     \
    "   Representa 10 iteraciones del Juego de la Vida en una matriz de "      \
    "20x20,\n"                                                                 \
    "   con un estado inicial tomado del archivo ‘‘glider’’.\n"        \
    "   Los archivos de salida se llamarán estado_n.pbm.\n"                   \
    "   Si no se da un prefijo para los archivos de salida,\n"                 \
    "   el prefijo será el nombre del archivo de entrada."

int main(int argc, char *argv[]) {
    int opt = 0;
    char *prefix_arg = NULL;
    bool interactive = false;
    while ((opt = getopt(argc, argv, "phvVo:-")) != -1) {
        switch (opt) {
        case 'h':
            printf("%s\n", help_message);
            return 0;
        case 'v':
        case 'V':
            printf("conway 0.0.1\n");
            return 0;
        case 'o':
            prefix_arg = optarg;
            break;
        case 'p':
            interactive = true;
            break;
        }
    }

    if ((argc < 5 || argc > 8) || ((argc == 6 || argc == 8) && !interactive) || ((argc == 7 || argc ==8) && !prefix_arg)) {
        fprintf(stderr, "Invalid arguments. Use conway -h to see valid examples. \n");
        return 1;
    }

    unsigned int I = atoi(argv[optind]);
    unsigned int M = atoi(argv[++optind]);
    unsigned int N = atoi(argv[++optind]);
    if (!I || !M || !N) {
        fprintf(stderr, "The arguments are not positive numbers\n");
        return 1;
    }

    char *matrix_name = argv[++optind];
    char *prefix = prefix_arg ? prefix_arg : matrix_name;

    matrix_t *matrix = matrix_create(matrix_name, M, N);
    if (!matrix) {
        fprintf(stderr, "Error creating the matrix\n");
        return 1;
    }

    printf("Reading initial state\n");
    if (interactive) {
        printf("Entering interactive mode:\n Press ENTER to see the next "
               "state\n Press ESC followed by ENTER to finish execution\n\n");
        char c = getchar();
        while (c != ESC) {
            matrix_print(matrix, stdout);
            matrix_update(matrix);
            c = getchar();
        }
        return 0;
    }

    for (int i = 0; i < I; i++) {
        if (!matrix_save(matrix, prefix))
            fprintf(stderr, "Error saving state %03d\n", i);
        else
            printf("Saving state %s_%03d.pbm\n", prefix, i);
        matrix_update(matrix);
    }

    matrix_destroy(matrix);
    printf("Done\n");
    return 0;
}
