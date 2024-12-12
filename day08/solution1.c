#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/init.h"

typedef struct {
    int m;
    int n;
    char name;
} antenna;

char** Collection;

int width;
int numNotDots;
antenna* Antennas;
int numAntinodes;

char** init_collection2();
void countNotDots();
void init_antennas();
void placeAntinodes();

int main(int argc, char* argv[]) {
    initialize(argc, argv);

    Collection = init_collection();

    width = strlen(Collection[0]) - 1;
    printf("width: %d\n", width);
    countNotDots();
    init_antennas();

    printf("numNotDots: %d\n", numNotDots);

    placeAntinodes();
    for (int i = 0; i < params.linecount; i++) {
        printf("%s", Collection[i]);
    }
    printf("numAntinodes: %d\n", numAntinodes);
}

// Counting how many 'not dots' there are in the input
void countNotDots() {
    numNotDots = 0;
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width; j++) {
            if (Collection[i][j] != '.') {
                numNotDots++;
            }
        }
    }
}

// Creating an array of antenna structs
void init_antennas() {
    Antennas = malloc(numNotDots * sizeof(antenna));
    printf("Allocating %d antennas\n", numNotDots);
    if (Antennas == NULL) {
        perror("Error allocating memory for Antennas\n");
        exit(EXIT_FAILURE);
    }

    int antennaCounter = 0;
    for (int i = 0; i < params.linecount; i++) {
        for (int j = 0; j < width; j++) {
            if (Collection[i][j] != '.') {
                Antennas[antennaCounter].m = i;
                Antennas[antennaCounter].n = j;
                Antennas[antennaCounter].name = Collection[i][j];
                antennaCounter++;
            }
        }
    }
}

// Calculating the number of antinodes and placing them all on the map
void placeAntinodes() {
    numAntinodes = 0;

    int mchange = 0;
    int nchange = 0;
    // Looping through every pair of antenna and checking if they have the same
    // name
    for (int i = 0; i < numNotDots; i++) {
        for (int j = 0; j < numNotDots; j++) {
            if (i == j) {
                continue;
            } else if (Antennas[i].name == Antennas[j].name) {
                mchange = Antennas[j].m - Antennas[i].m;
                nchange = Antennas[j].n - Antennas[i].n;

                // Checking if the proposed antinode is within bounds
                if (Antennas[j].m + mchange >= params.linecount ||
                    Antennas[j].m + mchange < 0) {
                    continue;
                } else if (Antennas[j].n + nchange >= width ||
                           Antennas[j].n + nchange < 0) {
                    continue;
                } else if (Collection[Antennas[j].m + mchange]
                                     [Antennas[j].n + nchange] == '#') {
                    continue;
                }
                numAntinodes++;
                printf("Antinode %d: %c (%d, %d)\n", numAntinodes,
                       Antennas[j].name, Antennas[j].m + mchange,
                       Antennas[j].n + nchange);

                Collection[Antennas[j].m + mchange][Antennas[j].n + nchange] =
                    '#';
            }
        }
    }
}
