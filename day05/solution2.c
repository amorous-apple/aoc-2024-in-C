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
int checkUpdateBool(char **Collection, int updateID);
int sumArr(int *arr, int length);
int *calcUpdateStatus(char **Collection);
int **makeInvUps(char **Collection);
int *countInvSize(char **Collection);
int properCheckOrder(int **Rules, int numRules, char a, char b);
int properCheckUpdateBool(int **Rules, int numRules, int *update,
                          int updateSize);
int *swapNums(int *arr, int ind1, int ind2);
int *cpyArr(int *dest, int *src, int length);
int *fixUpdate(int **Rules, int numRules, int *update, int updateSize);

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    char **Collection = init_collection();

    int numRules = countRules(Collection);
    int **Rules = init_rules(Collection);
    int numUpdates = countUpdates(Collection);
    int *updateStatus = calcUpdateStatus(Collection);
    int totalInv = numUpdates - sumArr(updateStatus, numUpdates);
    int *invCount = countInvSize(Collection);
    int **invUps = makeInvUps(Collection);

    printf("totalInv: %d\n", totalInv);

    for (int i = 0; i < totalInv; i++) {
        fixUpdate(Rules, numRules, invUps[i], invCount[i]);
    }

    int total = 0;
    for (int i = 0; i < totalInv; i++) {
        int mid = invCount[i] / 2;
        total += invUps[i][mid];
    }
    printf("Total: %d", total);
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

// Returning 1 if valid, otherwise return 0
int checkUpdateBool(char **Collection, int updateID) {
    if (!checkOrders(Collection, updateID)) {
        return 1;
    }
    return 0;
}

// Calculating the sum of all elements in an array
int sumArr(int *arr, int length) {
    int total = 0;
    for (int i = 0; i < length; i++) {
        total += arr[i];
    }
    return total;
}

// Calculating an array showing which of the initial updates are valid
int *calcUpdateStatus(char **Collection) {
    int numUpdates = countUpdates(Collection);
    int *statusList = malloc(numUpdates * sizeof(int));

    for (int i = 0; i < numUpdates; i++) {
        statusList[i] = checkUpdateBool(Collection, i);
    }
    return statusList;
}

// Creating a list of all invalid updates
int **makeInvUps(char **Collection) {
    int numUpdates = countUpdates(Collection);
    int *updateStats = calcUpdateStatus(Collection);
    int **Updates = init_updates(Collection);
    int *updateSize = countUpdateSize(Collection);
    int maxUpdate = maxVal(updateSize, numUpdates);

    int numInv = numUpdates - sumArr(updateStats, numUpdates);

    int *intArr = malloc(numInv * maxUpdate * sizeof(int));
    if (intArr == NULL) {
        perror("Error allocating memory for intArr\n");
        exit(EXIT_FAILURE);
    }

    int **invUps = malloc(numInv * sizeof(int *));
    if (invUps == NULL) {
        perror("Error allocating memory for invUps\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numInv; i++) {
        invUps[i] = intArr + i * maxUpdate;
    }

    int invCounter = 0;
    for (int i = 0; i < numUpdates; i++) {
        if (updateStats[i] != 1) {
            for (int j = 0; j < updateSize[i]; j++) {
                invUps[invCounter][j] = Updates[i][j];
            }
            invCounter++;
        }
    }

    return invUps;
}

// Creating a list of the update sizes for invalid updates
int *countInvSize(char **Collection) {
    int *updateSize = countUpdateSize(Collection);

    int numUpdates = countUpdates(Collection);
    int *upStat = calcUpdateStatus(Collection);
    int numInv = sumArr(upStat, numUpdates);

    int *invSize = malloc(numInv * sizeof(int));
    if (invSize == NULL) {
        perror("Error allocating memory for numUpdates\n");
        exit(EXIT_FAILURE);
    }

    int invSizeCount = 0;
    for (int i = 0; i < numUpdates; i++) {
        if (!upStat[i]) {
            invSize[invSizeCount] = updateSize[i];
            invSizeCount++;
        }
    }

    return invSize;
}

// Checking if the order of two integers is valid (returns 1 if false and 0 if
// true or otherwise)
int properCheckOrder(int **Rules, int numRules, char a, char b) {
    for (int i = 0; i < numRules; i++) {
        if (Rules[i][0] == b && Rules[i][1] == a) {
            return 1;
        }
    }
    return 0;
}

// Checking the order of an entire update line (return 1 invalid and 0
// otherwise)
int properCheckUpdateBool(int **Rules, int numRules, int *update,
                          int updateSize) {
    for (int i = 0; i < updateSize; i++) {
        for (int j = i + 1; j < updateSize; j++) {
            if (properCheckOrder(Rules, numRules, update[i], update[j])) {
                return 0;
            }
        }
    }
    return 1;
}

// Swapping two numbers in an array
int *swapNums(int *arr, int ind1, int ind2) {
    int temp = arr[ind1];
    arr[ind1] = arr[ind2];
    arr[ind2] = temp;
    return arr;
}

int *cpyArr(int *dest, int *src, int length) {
    for (int i = 0; i < length; i++) {
        dest[i] = src[i];
    }
    return dest;
}

// 'Fixing' an update so that it complies with the rules
int *fixUpdate(int **Rules, int numRules, int *update, int updateSize) {
    if (properCheckUpdateBool(Rules, numRules, update, updateSize)) {
        // printf("Update already valid.\n");
        return update;
    }

    for (int i = 0; i < updateSize; i++) {
        for (int j = i + 1; j < updateSize; j++) {
            if (!(properCheckOrder(Rules, numRules, update[i], update[j]))) {
                continue;
            } else {
                swapNums(update, i, j);
            }
        }
    }
    if (!properCheckUpdateBool(Rules, numRules, update, updateSize)) {
        update = fixUpdate(Rules, numRules, update, updateSize);
    }

    return update;
}
