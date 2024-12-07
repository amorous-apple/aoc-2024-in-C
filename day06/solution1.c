#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/init.h"

int *init_guard();
int countX();
void moveGuard();

char **Collection;

// Declaring a global width of the system and the current position of the guard
int width;
int *posGuard;

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    Collection = init_collection();

    width = strlen(Collection[0]);
    init_guard();

    moveGuard();
    Collection[posGuard[0]][posGuard[1]] = 'X';

    int countOfX = countX();

    printf("# count: %d\n", countOfX);
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

// Counting the number of 'X's found in Collection
int countX() {
    int count = 0;
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width; j++) {
            if (Collection[i][j] == 'X') {
                count++;
            }
        }
    }
    return count;
}

// Moving the guard according to its rules and placing an X behind every
// movement
void moveGuard() {
    // Choosing movement directions based on the guard's orientation
    char guardStatus = Collection[posGuard[0]][posGuard[1]];
    switch (guardStatus) {
        case '^':
            if (posGuard[0] == 0) {
                printf("Guard reached top\n");
                break;
            }
            // Turning the guard if it is in front of an obstruction
            if (Collection[posGuard[0] - 1][posGuard[1]] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '>';
                moveGuard();
                break;
            }
            // Placing an 'X' behind the guard and moving it one tile forward
            Collection[posGuard[0]][posGuard[1]] = 'X';
            Collection[posGuard[0] - 1][posGuard[1]] = '^';
            posGuard[0]--;
            moveGuard();
            break;
        case '>':
            if (posGuard[1] == width - 1) {
                printf("Guard reached right\n");
                break;
            }
            if (Collection[posGuard[0]][posGuard[1] + 1] == '#') {
                Collection[posGuard[0]][posGuard[1]] = 'v';
                moveGuard();
                break;
            }
            Collection[posGuard[0]][posGuard[1]] = 'X';
            Collection[posGuard[0]][posGuard[1] + 1] = '>';
            posGuard[1]++;
            moveGuard();
            break;
        case 'v':
            if (posGuard[0] == params.linecount - 1) {
                printf("Guard reached bottom\n");
                break;
            }
            if (Collection[posGuard[0] + 1][posGuard[1]] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '<';
                moveGuard();
                break;
            }
            Collection[posGuard[0]][posGuard[1]] = 'X';
            Collection[posGuard[0] + 1][posGuard[1]] = 'v';
            posGuard[0]++;
            moveGuard();
            break;
        case '<':
            if (posGuard[1] == 0) {
                printf("Guard reached left\n");
                break;
            }
            if (Collection[posGuard[0]][posGuard[1] - 1] == '#') {
                Collection[posGuard[0]][posGuard[1]] = '^';
                moveGuard();
                break;
            }
            Collection[posGuard[0]][posGuard[1]] = 'X';
            Collection[posGuard[0]][posGuard[1] - 1] = '<';
            posGuard[1]--;
            moveGuard();
            break;
    }
}
