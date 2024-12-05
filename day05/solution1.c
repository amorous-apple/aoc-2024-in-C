#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

int countRules(char **Collection);
int countUpdates(char **Collection);
int **init_rules(char **Collection);
int *countUpdateSize(char **Collection);
int maxVal(int *arr, int arrSize);
int **init_updates(char **Collection);
int checkOrder(char **Collection, int a, int b);
int checkOrders(char **Collection, int updateID);
int checkUpdate(char **Collection, int updateID);

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    char **Collection = init_collection();

    int numUpdates = countUpdates(Collection);

    int total = 0;
    // Checking every update to make sure that it is valid
    for (int i = 0; i < numUpdates; i++) {
        total += checkUpdate(Collection, i);
    }
    printf("Total mids: %d\n", total);
}

// Calculating how many page rules there are in Collection
int countRules(char **Collection) {
    int numRules = 0;
    for (int i = 0; i < params.linecount - 1; i++) {
        if (Collection[i][2] != '|') {
            numRules = i;
            break;
        }
    }
    return numRules;
}

int countUpdates(char **Collection) {
    int numRules = countRules(Collection);
    int numUpdates = params.linecount - numRules - 1;
    return numUpdates;
}

int **init_rules(char **Collection) {
    int numRules = countRules(Collection);

    int *intArr = malloc(numRules * 2 * sizeof(int));
    if (intArr == NULL) {
        perror("Error allocating memory for intArr\n");
        exit(EXIT_FAILURE);
    }
    int **Rules = malloc(numRules * sizeof(int *));
    if (Rules == NULL) {
        perror("Error allocating memory for Rules\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numRules; i++) {
        Rules[i] = intArr + (i * 2);
    }

    for (int i = 0; i < numRules; i++) {
        Rules[i][0] = ((Collection[i][0] - '0') * 10) + Collection[i][1] - '0';
        Rules[i][1] = ((Collection[i][3] - '0') * 10) + Collection[i][4] - '0';
    }

    return Rules;
}

int *countUpdateSize(char **Collection) {
    int numRules = countRules(Collection);
    int numUpdates = countUpdates(Collection);

    int *updateSize = malloc(numUpdates * sizeof(int));
    if (updateSize == NULL) {
        perror("Error allocating memory for numUpdates\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numUpdates; i++) {
        updateSize[i] = (strlen(Collection[numRules + i]) + 1) / 3;
    }

    return updateSize;
}

// Calculating the largest value in an array
int maxVal(int *arr, int arrSize) {
    int maximum = arr[0];
    for (int i = 1; i < arrSize; i++) {
        if (arr[i] > maximum) {
            maximum = arr[i];
        }
    }
    return maximum;
}

int **init_updates(char **Collection) {
    int numRules = countRules(Collection);
    int numUpdates = countUpdates(Collection);
    int *updateSize = countUpdateSize(Collection);

    int maxUpdate = maxVal(updateSize, numUpdates);

    int *intArr = malloc(numUpdates * maxUpdate * sizeof(int));
    if (intArr == NULL) {
        perror("Error allocating memory for Updates\n");
        exit(EXIT_FAILURE);
    }

    int **Updates = malloc(numUpdates * sizeof(int *));
    if (Updates == NULL) {
        perror("Error allocating memory for Updates\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numUpdates; i++) {
        Updates[i] = intArr + i * maxUpdate;
    }

    for (int i = 0; i < numUpdates; i++) {
        for (int j = 0; j < updateSize[i]; j++) {
            Updates[i][j] = ((Collection[numRules + i][3 * j] - '0') * 10) +
                            (Collection[numRules + i][3 * j + 1] - '0');
        }
    }
    return Updates;
}

// Checking if the order of two integers is valid (returns 1 if false and 0 if
// true or otherwise)
int checkOrder(char **Collection, int a, int b) {
    int numRules = countRules(Collection);
    int **Rules = init_rules(Collection);

    for (int i = 0; i < numRules; i++) {
        if (Rules[i][0] == b && Rules[i][1] == a) {
            return 1;
        }
    }
    return 0;
}

// Checking the order of an entire update line (return 1 invalid and 0
// otherwise)
int checkOrders(char **Collection, int updateID) {
    int *updateSize = countUpdateSize(Collection);
    int currentUpSize = updateSize[updateID];
    int **Update = init_updates(Collection);
    int *currentUp = Update[updateID];

    for (int i = 0; i < currentUpSize; i++) {
        for (int j = i + 1; j < currentUpSize; j++) {
            if (checkOrder(Collection, currentUp[i], currentUp[j])) {
                return 1;
            }
        }
    }

    return 0;
}

// Returning the middle value of an update if valid, otherwise return 0
int checkUpdate(char **Collection, int updateID) {
    int *updateSize = countUpdateSize(Collection);
    int currentUpSize = updateSize[updateID];
    int **Update = init_updates(Collection);
    int *currentUp = Update[updateID];

    int mid = currentUpSize / 2;

    if (!checkOrders(Collection, updateID)) {
        return currentUp[mid];
    }
    return 0;
}
