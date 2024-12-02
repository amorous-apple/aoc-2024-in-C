#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>

#include "constants.h"

typedef struct {
    char* input;
    int linecount;
    int dataSize;
} Parameters;

extern Parameters params;

void initialize(int argc, char* argv[]);
FILE* init_input();
char** init_collection1();
void data_read(char** Collection, FILE* psrcfile);

int countLine(char* filename);

#endif
