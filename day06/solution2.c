#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/constants.h"
#include "lib/init.h"

int *init_guard();
int *init_tmpGuard();
void cpyGuard(int *tmpPosGuard, int *srcPosGuard);
int moveGuard();
char **init_tmpCollection();
void cpyCollection(char **tmpCollection, char **srcCollection);

char **Collection;

// Declaring a global width of the system and the current position of the guard
int width;
int *posGuard;

// Declaring a maximum number of permitted turns that the guard can make
const int MAX_TURNS = 5000;
int turns;

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    Collection = init_collection();

    width = strlen(Collection[0]);
    init_guard();

    char **tmpCollection = init_tmpCollection();
    cpyCollection(tmpCollection, Collection);
    int *tmpPosGuard = init_tmpGuard();
    cpyGuard(tmpPosGuard, posGuard);

    int loopCount = 0;

    // Checking every potential obstruction placement for loop generation
    // #pragma omp parallel for
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width - 1; j++) {
            // Preventing the placement of obstructions on the guard or on
            // existing obstructions
            if (i == tmpPosGuard[0] && j == tmpPosGuard[1]) {
                continue;
            } else if (tmpCollection[i][j] == '#') {
                continue;
            }

            // Saving the initial Collection and guard position
            cpyCollection(Collection, tmpCollection);
            cpyGuard(posGuard, tmpPosGuard);
            Collection[i][j] = '#';

            turns = 0;
            int loopStatus = moveGuard();
            if (loopStatus) {
                loopCount++;
            }
            // printf("===========Loop (%d, %d), Loop Status: %d\n ", i, j,
            //        loopStatus);
            // for (int i = 0; i < params.linecount; i++) {
            //     printf("Line %d: %s \n", i, Collection[i]);
            // }
        }
    }
    printf("loopCount: %d", loopCount);
}

char **init_tmpCollection() {
    // Allocating memory for all chars in input
    char *charArr = malloc(params.linecount * MAX_LINE_LENGTH * sizeof(char));
    if (charArr == NULL) {
        perror("Error allocating memory for charArr. \n");
        exit(EXIT_FAILURE);
    }

    // Allocating memory for pointers to every row
    char **tmpCollection = malloc(params.linecount * sizeof(char *));
    if (tmpCollection == NULL) {
        perror("Error allocating memory for tmpCollection. \n");
        exit(EXIT_FAILURE);
    }
    // Assigning the pointers for the beginning of every row
    for (int i = 0; i < params.linecount; i++) {
        tmpCollection[i] = charArr + (i * MAX_LINE_LENGTH);
    }

    return tmpCollection;
}

// Copying srcCollection to tmpCollection
void cpyCollection(char **tmpCollection, char **srcCollection) {
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width; j++) {
            tmpCollection[i][j] = srcCollection[i][j];
        }
    }
}

// Making a 2D vector to contain the guard's position
int *init_guard() {
    posGuard = malloc(2 * sizeof(int));
    if (posGuard == NULL) {
        perror("Error allocating memory for posGuard\n");
        exit(EXIT_FAILURE);
    }
    posGuard[0] = 0;
    posGuard[1] = 0;

    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width; j++) {
            if (Collection[i][j] == '^') {
                posGuard[0] = i;
                posGuard[1] = j;
                return posGuard;
            }
        }
    }
    return posGuard;
}

int *init_tmpGuard() {
    int *tmpPosGuard = malloc(2 * sizeof(int));
    if (tmpPosGuard == NULL) {
        perror("Error allocating memory for posGuard\n");
        exit(EXIT_FAILURE);
    }
    return tmpPosGuard;
}

// Copying srcPosGuard to tmpPosGuard
void cpyGuard(int *tmpPosGuard, int *srcPosGuard) {
    tmpPosGuard[0] = srcPosGuard[0];
    tmpPosGuard[1] = srcPosGuard[1];
}

// Moving the guard. Returns 1 if the guard is in a loop and 0 otherwise
int moveGuard() {
    // Preventing infinite loops by tracking turns
    if (turns > MAX_TURNS) {
        return 1;
    }

    // Choosing movement directions based on the guard's orientation
    char guardStatus = Collection[posGuard[0]][posGuard[1]];
    switch (guardStatus) {
        case '^':
            if (posGuard[0] == 0) {
                // printf("Guard reached top\n");
                return 0;

                // Turning the guard if it is in front of an obstruction
            } else if (Collection[posGuard[0] - 1][posGuard[1]] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '>';
                turns++;
                return moveGuard();
                break;

                // Placing a 'u' (up) to indicate which direction the guard went
                // and moving it one tile up
            } else if (Collection[posGuard[0] - 1][posGuard[1]] == 'u') {
                return 1;
            } else {
                Collection[posGuard[0]][posGuard[1]] = 'u';
                Collection[posGuard[0] - 1][posGuard[1]] = '^';
                posGuard[0]--;
                return moveGuard();
                break;
            }
        case '>':
            if (posGuard[1] == width - 1) {
                // printf("Guard reached right\n");
                return 0;
            } else if (Collection[posGuard[0]][posGuard[1] + 1] == '#') {
                Collection[posGuard[0]][posGuard[1]] = 'v';
                turns++;
                return moveGuard();
                break;
            } else if (Collection[posGuard[0]][posGuard[1] + 1] == 'r') {
                return 1;
            } else {
                Collection[posGuard[0]][posGuard[1]] = 'r';
                Collection[posGuard[0]][posGuard[1] + 1] = '>';
                posGuard[1]++;
                return moveGuard();
                break;
            }
        case 'v':
            if (posGuard[0] == params.linecount - 1) {
                // printf("Guard reached bottom\n");
                return 0;
            } else if (Collection[posGuard[0] + 1][posGuard[1]] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '<';
                turns++;
                return moveGuard();
                break;
            } else if (Collection[posGuard[0] + 1][posGuard[1]] == 'd') {
                return 1;
            } else {
                Collection[posGuard[0]][posGuard[1]] = 'd';
                Collection[posGuard[0] + 1][posGuard[1]] = 'v';
                posGuard[0]++;
                return moveGuard();
                break;
            }
        case '<':
            if (posGuard[1] == 0) {
                // printf("Guard reached left\n");
                return 0;
            } else if (Collection[posGuard[0]][posGuard[1] - 1] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '^';
                turns++;
                return moveGuard();
                break;
            } else if (Collection[posGuard[0]][posGuard[1] - 1] == 'l') {
                return 1;
            } else {
                Collection[posGuard[0]][posGuard[1]] = 'l';
                Collection[posGuard[0]][posGuard[1] - 1] = '<';
                posGuard[1]--;
                return moveGuard();
                break;
            }
    }
    return 0;
}
