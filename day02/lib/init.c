#include "init.h"

Parameters params;

void initialize(int argc, char* argv[]) {
    if (argc == 2) {
        params.input = argv[1];
    } else {
        params.input = "./input.txt";
    }
    params.linecount = countLine(params.input);
    params.dataSize = sizeof(Data);
}

FILE* init_input() {
    FILE* srcfile = fopen(params.input, "r");
    if (ferror(srcfile)) {
        perror("Error openeing input file. \n");
        exit(EXIT_FAILURE);
    }
    return srcfile;
}

char** init_collection1() {
    char** Collection1 = malloc(params.linecount * sizeof(char*));
    if (Collection1 == NULL) {
        perror("Error allocating memory for Collection 1. \n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        Collection1[i] = malloc(128 * sizeof(char));
        if (Collection1[i] == NULL) {
            perror("Error allocating memory for collection[i]\n");
            exit(EXIT_FAILURE);
        }
    }

    return Collection1;
}

// A function that returns the number of lines in a file
int countLine(char* filename) {
    // Lines are counted in blocks of 64 kb at a time
    const int BUF_SIZE = 65536;
    FILE* pfile = fopen(filename, "r");
    if (pfile == NULL) {
        perror("Error opening file 1");
        exit(EXIT_FAILURE);
    }

    char buf[BUF_SIZE];
    int counter = 0;

    for (;;) {
        size_t chars = fread(buf, 1, BUF_SIZE, pfile);
        if (ferror(pfile)) {
            perror("Error opening file 2");
            exit(EXIT_FAILURE);
        }
        for (size_t i = 0; i < chars; i++) {
            if (buf[i] == '\n') {
                counter++;
            }
        }
        if (feof(pfile)) {
            break;
        }
    }
    fclose(pfile);
    return counter;
}

// Reading and storing the data for the lines in Collection
void data_read(char** Collection, FILE* psrcfile) {
    for (int i = 0; i < params.linecount; i++) {
        if (!fgets(Collection[i], 128, psrcfile)) {
            printf("Error reading data for line %i \n", i);
            free(Collection);
            fclose(psrcfile);
            exit(EXIT_FAILURE);
        }
    }
}
