#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int opt;
    char* prefix = NULL;
    while ((opt = getopt(argc, argv, "hvo:")) != -1) {
        switch (opt) {
            case 'h':
                printf("Use: conway i M N inputfile [-o outputprefix]\n");
                return 0;
            case 'v':
                printf("conway 0.0.1\n");
                return 0;
            case 'o':
                prefix = optarg;
        }
    }

    int I = atoi(argv[optind]);
    int M = atoi(argv[++optind]);
    int N = atoi(argv[++optind]);
    if (!I || !M || !N)
        fprintf(stderr, "The arguments are not positive numbers\n");

    char* matrix_name = argv[++optind];
    FILE* matrix = fopen(matrix_name, "r");
    if (!matrix) fprintf(stderr, "The matrix file does not exist\n");

    printf("Reading initial state\n");
    for (int i = 0; i < I; i++) {
        char fname[1024];
        sprintf(fname, "%s_%d.pbm", prefix ? prefix : matrix_name, i);
        FILE* f = fopen(fname, "w");
        printf("Saving %s\n", fname);
        fclose(f);
    }
    printf("Done\n");
    fclose(matrix);
}
