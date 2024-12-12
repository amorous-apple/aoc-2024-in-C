#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

char **Collection;
int *testVals;
int **Numbers;
int *countNumbers;

void init_testVals();
void init_Numbers();

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    Collection = init_collection();
    init_testVals();
    init_Numbers();

    for (int i = 0; i < params.linecount; i++) {
        // printf("Line %d: %s\n", i, Collection[i]);
        printf("testVal %d: %d, count: %d\n", i + 1, testVals[i],
               countNumbers[i]);
        printf("\t Numbers: ");
        for (int j = 0; j < countNumbers[i]; j++) {
            printf("%d, ", Numbers[i][j]);
        }
        printf("\n");
    }

    free(Collection[0]);
    free(Collection);
    free(testVals);
    free(Numbers[0]);
    free(Numbers);
    free(countNumbers);
}

void init_testVals() {
    testVals = malloc(params.linecount * sizeof(int));
    if (testVals == NULL) {
        perror("Error allocating memory for testVals\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        char *equation = strdup(Collection[i]);
        if (equation == NULL) {
            perror("Error duplicating to equation\n");
            exit(EXIT_FAILURE);
        }
        testVals[i] = atoi(strtok(equation, ":"));
    }
}

void init_Numbers() {
    int *intArr = malloc(params.linecount * MAX_LINE_LENGTH * sizeof(int));
    if (intArr == NULL) {
        perror("Error allocating memory for intArr\n");
        exit(EXIT_FAILURE);
    }
    Numbers = malloc(params.linecount * sizeof(int *));
    if (Numbers == NULL) {
        perror("Error allocating memory for Numbers\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        Numbers[i] = intArr + i * MAX_LINE_LENGTH;
    }

    countNumbers = malloc(params.linecount * sizeof(int));
    if (countNumbers == NULL) {
        perror("Error allocating memory for countNumbers\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < params.linecount; i++) {
        char *equation = strdup(Collection[i]);
        if (equation == NULL) {
            perror("Error duplicating to equation\n");
            exit(EXIT_FAILURE);
        }

        int countNums = 0;
        char *number = strtok(equation, " ");
        number = strtok(NULL, " ");
        while (number != NULL) {
            Numbers[i][countNums++] = atoi(number);
            number = strtok(NULL, " ");
        }

        countNumbers[i] = countNums;
    }
}
