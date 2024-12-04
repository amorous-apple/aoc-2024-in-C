#ifndef INIT_H
#define INIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"

typedef struct {
    char* input;
    int wordlength;
    int linecount;
    int linelength;
} Parameters;

extern Parameters params;

void initialize(int argc, char* argv[], const char* WORD);
FILE* init_input();
char **init_collection();
void data_read(char **Collection, FILE* psrcfile);

int countLine(char* filename);

#endif
