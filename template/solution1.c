#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

char **Collection;

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    Collection = init_collection();

    for (int i = 0; i < params.linecount; i++) {
        printf("Line %d: %s \n", i, Collection[i]);
    }
}
