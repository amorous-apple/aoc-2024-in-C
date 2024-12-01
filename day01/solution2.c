#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    // Opening the input file and storing its data in a buffer
    FILE *srcfile = init_input();
    Data *Collection1 = init_collection1();

    data_read(Collection1, srcfile);

    // Splitting the data into two arrays
    int *xdata = malloc(params.linecount * sizeof(int));
    int *ydata = malloc(params.linecount * sizeof(int));
    if (xdata == NULL || ydata == NULL) {
        perror("Error allocating xdata and/ or ydata.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < params.linecount; i++) {
        xdata[i] = Collection1[i].x;
        ydata[i] = Collection1[i].y;
    }

    int n = params.linecount;

    // Sorting both arrays
    quickSort(xdata, 0, n - 1);
    quickSort(ydata, 0, n - 1);

    // Finding the largest value present to make an array containing their count
    int xmax = xdata[params.linecount - 1];
    int ymax = ydata[params.linecount - 1];

    int max;
    if (xmax > ymax) {
        max = xmax;
    } else {
        max = ymax;
    }

    // Allocating memory for an array containing the frequency of each number
    int *rightLsCount = malloc((max + 1) * sizeof(int));
    if (rightLsCount == NULL) {
        perror("Error allocating rightLsCount. \n");
        exit(EXIT_FAILURE);
    }

    // Initializing the array to all 0s
    for (int i = 0; i < max + 1; i++) {
        rightLsCount[i] = 0;
    }
    // Incrementing the appropriate index of the array whenever the number is
    // found in ydata
    for (int i = 0; i < params.linecount; i++) {
        rightLsCount[ydata[i]]++;
    }

    // Calculating and adding the 'similarity' for each line
    int totalSim = 0;
    for (int i = 0; i < params.linecount; i++) {
        totalSim += (int)xdata[i] * rightLsCount[xdata[i]];
    }

    printf("The total is: %d \n", totalSim);
}
