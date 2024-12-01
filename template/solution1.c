#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/algorithms.h"
#include "lib/constants.h"
#include "lib/init.h"
#include "lib/utils_vec.h"

int main(int argc, char *argv[]) {
    initialize(argc, argv);

    // Opening the input file and storing its data in a buffer
    FILE *srcfile = init_input();
    Data *Collection1 = init_collection1();

    data_read(Collection1, srcfile);

    for (int i = 0; i < params.linecount; i++) {
    }
}
