#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

const char *WORD = "MAS";

int wordCounter(const char *word, char **Collection, int i, int j);

int searchNW(char letter, char **Collection, int i, int j);
int searchNE(char letter, char **Collection, int i, int j);
int searchSE(char letter, char **Collection, int i, int j);
int searchSW(char letter, char **Collection, int i, int j);

int main(int argc, char *argv[]) {
    initialize(argc, argv, WORD);
    char **Collection = init_collection();

    int totalCount = 0;

    // Searching for WORD crosses within the bounds of Collection
    for (int i = 1; i < params.linecount - 1; i++) {
        for (int j = 1; j < params.linelength - 1; j++) {
            totalCount += wordCounter(WORD, Collection, i, j);
        }
    }
    printf("totalCount : %i\n", totalCount);
}

// Checking if there is a cross of 'word' at (i,j)
int wordCounter(const char *word, char **Collection, int i, int j) {
    int subCount = 0;
    // Terminates the search for the cross if the char at (i,j) does not match
    // the middle character of WORD
    if (Collection[i][j] != word[1]) {
        return 0;
    } else {
        // Checking the top left to bottom right diagonal
        if (((searchNW(WORD[0], Collection, i, j) &&
              searchSE(WORD[2], Collection, i, j)) ||
             (searchNW(WORD[2], Collection, i, j) &&
              searchSE(WORD[0], Collection, i, j))) &&
            // Checking the top right to bottom left diagonal
            ((searchNE(WORD[0], Collection, i, j) &&
              searchSW(WORD[2], Collection, i, j)) ||
             (searchNE(WORD[2], Collection, i, j) &&
              searchSW(WORD[0], Collection, i, j)))) {
            return 1;
        } else {
            return 0;
        }
    }

    return subCount;
}

// Checking for 'letter' to the NW of (i,j)
int searchNW(char letter, char **Collection, int i, int j) {
    if (Collection[i - 1][j - 1] == letter) {
        return 1;
    } else {
        return 0;
    }
}
// Checking for 'letter' to the NE of (i,j)
int searchNE(char letter, char **Collection, int i, int j) {
    if (Collection[i - 1][j + 1] == letter) {
        return 1;
    } else {
        return 0;
    }
}
// Checking for 'letter' to the SE of (i,j)
int searchSE(char letter, char **Collection, int i, int j) {
    if (Collection[i + 1][j + 1] == letter) {
        return 1;
    } else {
        return 0;
    }
}
// Checking for 'letter' to the SW of (i,j)
int searchSW(char letter, char **Collection, int i, int j) {
    if (Collection[i + 1][j - 1] == letter) {
        return 1;
    } else {
        return 0;
    }
}
