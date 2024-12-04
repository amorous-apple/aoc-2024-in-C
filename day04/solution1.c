#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

const char *WORD = "XMAS";

int wordCounter(const char *word, char **Collection, int i, int j);

int searchNW(const char *word, char **Collection, int i, int j, int searchInd);
int searchN(const char *word, char **Collection, int i, int j, int searchInd);
int searchNE(const char *word, char **Collection, int i, int j, int searchInd);
int searchE(const char *word, char **Collection, int i, int j, int searchInd);
int searchSE(const char *word, char **Collection, int i, int j, int searchInd);
int searchS(const char *word, char **Collection, int i, int j, int searchInd);
int searchSW(const char *word, char **Collection, int i, int j, int searchInd);
int searchW(const char *word, char **Collection, int i, int j, int searchInd);

int main(int argc, char *argv[]) {
    initialize(argc, argv, WORD);
    char **Collection = init_collection();

    int totalCount = 0;

    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < params.linelength; j++) {
            totalCount += wordCounter(WORD, Collection, i, j);
        }
    }
    printf("totalCount : %i\n", totalCount);
}

// Counting the instances of 'word' starting at the point (i, j) in the
// Collection
int wordCounter(const char *word, char **Collection, int i, int j) {
    int subCount = 0;
    // Terminates the search for the word if the first letter does not match
    if (Collection[i][j] != word[0]) {
        return subCount;
    } else {
        int downSpace = params.linecount - i;
        int rightSpace = params.linelength - j;

        // Searching for the presence of the word in eight directions
        // 'if' statements prevent searching when not enough space
        if (i + 1 >= params.wordlength && j + 1 >= params.wordlength) {
            subCount += searchNW(word, Collection, i, j, 1);
        }
        if (i + 1 >= params.wordlength) {
            subCount += searchN(word, Collection, i, j, 1);
        }
        if (i + 1 >= params.wordlength && rightSpace >= params.wordlength) {
            subCount += searchNE(word, Collection, i, j, 1);
        }
        if (rightSpace >= params.wordlength) {
            subCount += searchE(word, Collection, i, j, 1);
        }
        if (downSpace >= params.wordlength && rightSpace >= params.wordlength) {
            subCount += searchSE(word, Collection, i, j, 1);
        }
        if (downSpace >= params.wordlength) {
            subCount += searchS(word, Collection, i, j, 1);
        }
        if (j + 1 >= params.wordlength && downSpace >= params.wordlength) {
            subCount += searchSW(word, Collection, i, j, 1);
        }
        if (j + 1 >= params.wordlength) {
            subCount += searchW(word, Collection, i, j, 1);
        }
    }

    return subCount;
}

// Returning 1 if 'word' is found to the northwest of (i,j) and otherwise 0
int searchNW(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i - searchInd][j - searchInd] == word[searchInd]) {
        return searchNW(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}

// Returning 1 if 'word' is found to the north of (i,j) and otherwise 0
int searchN(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i - searchInd][j] == word[searchInd]) {
        return searchN(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}

// Returning 1 if 'word' is found to the northeast of (i,j) and otherwise 0
int searchNE(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i - searchInd][j + searchInd] == word[searchInd]) {
        return searchNE(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
// Returning 1 if 'word' is found to the east of (i,j) and otherwise 0
int searchE(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i][j + searchInd] == word[searchInd]) {
        return searchE(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
// Returning 1 if 'word' is found to the southeast of (i,j) and otherwise 0
int searchSE(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i + searchInd][j + searchInd] == word[searchInd]) {
        return searchSE(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
// Returning 1 if 'word' is found to the south of (i,j) and otherwise 0
int searchS(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i + searchInd][j] == word[searchInd]) {
        return searchS(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
// Returning 1 if 'word' is found to the southwest of (i,j) and otherwise 0
int searchSW(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i + searchInd][j - searchInd] == word[searchInd]) {
        return searchSW(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
// Returning 1 if 'word' is found to the west of (i,j) and otherwise 0
int searchW(const char *word, char **Collection, int i, int j, int searchInd) {
    if (searchInd == params.wordlength) {
        return 1;
    } else if (Collection[i][j - searchInd] == word[searchInd]) {
        return searchW(word, Collection, i, j, searchInd + 1);
    }
    return 0;
}
