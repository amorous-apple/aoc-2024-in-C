#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/init.h"

const int MAX_NUMS_PER_LINE = 8;

int numCount(char *line);
int *strParse(char *line, int *intLine);
int isSafe(int *diffs);
int *rmVal(int index, int *array);
void arrcpy(int *dest, int *src, int leng);

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    // Opening the input file and storing its data in a buffer
    FILE *srcfile = init_input();
    char **Collection1 = init_collection1();

    // Creating an array of strings storing all of the data
    data_read(Collection1, srcfile);

    // Allocating memory for all of he values in the input data
    int *intArray = malloc(params.linecount * MAX_NUMS_PER_LINE * sizeof(int));
    if (intArray == NULL) {
        perror("Error allocating memory for intColl1\n");
        exit(EXIT_FAILURE);
    }
    // Creating pointers for all of the rows of data
    int **intRow1 = malloc(params.linecount * sizeof(int *));
    if (intRow1 == NULL) {
        perror("Error allocating memory for intRow1\n");
        exit(EXIT_FAILURE);
    }
    // Assigning the pointers for each row
    for (int i = 0; i < params.linecount; i++) {
        intRow1[i] = intArray + (i * MAX_NUMS_PER_LINE);
    }

    // Creating an array of ints to store the number of numbers that each line
    // contains
    int *numCountArray = malloc(params.linecount * sizeof(int));
    if (numCountArray == NULL) {
        perror("Error allocating memory for numCountArray\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        numCountArray[i] = numCount(Collection1[i]);
    }

    // Parsing all of the strings into a 2D array of ints
    for (int i = 0; i < params.linecount; i++) {
        intRow1[i] = strParse(Collection1[i], intRow1[i]);
    }
    free(Collection1);

    // Creating a matrix with all of the differences between the numbers in the
    // Data
    int *diffMat =
        malloc(params.linecount * (MAX_NUMS_PER_LINE - 1) * sizeof(int));
    if (diffMat == NULL) {
        perror("Error allocating memory for diffMat\n");
        exit(EXIT_FAILURE);
    }
    int **diffRows = malloc(params.linecount * sizeof(int *));
    if (diffRows == NULL) {
        perror("Error allocating memory for diffRows\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        diffRows[i] = diffMat + (i * (MAX_NUMS_PER_LINE - 1));
    }
    // Initializing all of the differences to 9999
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < MAX_NUMS_PER_LINE - 1; j++) {
            diffRows[i][j] = 9999;
        }
    }

    // Calculating all of the appropriate differences
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < numCountArray[i] - 1; j++) {
            diffRows[i][j] = intRow1[i][j + 1] - intRow1[i][j];
        }
    }

    // Allocating an array to keep track of safe lines
    int *safeArray = malloc(params.linecount * sizeof(int));
    if (safeArray == NULL) {
        perror("Error allocating memory for safeArray\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        safeArray[i] = isSafe(diffRows[i]);
    }

    // Calculating the "total safety"
    int safeTotal = 0;
    for (int i = 0; i < params.linecount; i++) {
        safeTotal += safeArray[i];
    }

    int *tempArray = malloc(MAX_NUMS_PER_LINE * sizeof(int));
    int *tempDiffs = malloc((MAX_NUMS_PER_LINE - 1) * sizeof(int));
    for (int i = 0; i < params.linecount; i++) {
        if (safeArray[i]) {
            continue;
        }
        // Checking if an array is safe after removing the value at index j
        for (int j = 0; j < numCountArray[i]; j++) {
            arrcpy(tempArray, intRow1[i], MAX_NUMS_PER_LINE);
            rmVal(j, tempArray);

            // Wiping the values of tempDiffs
            for (int k = 0; k < MAX_NUMS_PER_LINE - 1; k++) {
                tempDiffs[k] = 9999;
            }
            // Writing the values for tempDiffs
            for (int k = 0; k < numCountArray[i] - 2; k++) {
                tempDiffs[k] = tempArray[k + 1] - tempArray[k];
            }

            // Checking if the newly created line is safe
            if (isSafe(tempDiffs)) {
                safeTotal++;
                break;
            }
        }
    }

    printf("safeTotal2: %d", safeTotal);
}

// Turning a string of space-separated numbers into an array of ints
int *strParse(char *line, int *intLine) {
    char *token = strtok(line, " ");
    int i = 0;

    while (token != NULL) {
        intLine[i] = atoi(token);

        token = strtok(NULL, " ");
        i++;
    }

    return intLine;
}

// Counting the number of numbers (separated by spaces) in a string
int numCount(char *line) {
    int spaces = 0;
    for (size_t i = 0; i < strlen(line); i++) {
        if (line[i] == ' ') {
            spaces++;
        }
    }
    int numCount = spaces + 1;
    return numCount;
}

// Testing if a row of differences is safe
int isSafe(int *diffs) {
    // Checking for diffs = 0 or |diffs| > 3
    for (int i = 0; i < MAX_NUMS_PER_LINE - 1; i++) {
        if (diffs[i] == 0) {
            return 0;
        }
        if (abs(diffs[i]) > 3 && diffs[i] < 9999) {
            return 0;
        }
    }

    // Checking if all diffs are positive
    if (diffs[0] > 0) {
        for (int i = 1; i < MAX_NUMS_PER_LINE - 1; i++) {
            if (diffs[i] < 0 && diffs[i] != 9999) {
                return 0;
            }
        }
    }

    // Checking if all diffs are negative
    if (diffs[0] < 0) {
        for (int i = 1; i < MAX_NUMS_PER_LINE - 1; i++) {
            if (diffs[i] > 0 && diffs[i] != 9999) {
                return 0;
            }
        }
    }
    return 1;
}

// Removing the value at index from the given array
int *rmVal(int index, int *array) {
    for (int i = index; i < MAX_NUMS_PER_LINE - 1; i++) {
        array[i] = array[i + 1];
    }
    array[MAX_NUMS_PER_LINE - 1] = 0;

    return array;
}

// Copy an integer array from source to destination
void arrcpy(int *dest, int *src, int leng) {
    for (int i = 0; i < leng; i++) {
        dest[i] = src[i];
    }
}
