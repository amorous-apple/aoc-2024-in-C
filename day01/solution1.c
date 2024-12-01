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

    // Calculating the differences, summing them, and printing the result
    int total = 0;
    for (int i = 0; i < params.linecount; i++) {
        total += abs(xdata[i] - ydata[i]);
    }
    printf("The total is: %d \n", total);
}
