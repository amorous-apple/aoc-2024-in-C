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

    char **Collection = init_collection();

    for (int i = 0; i < params.linecount; i++) {
        printf("==== LINE %d ====\n", i);
        // puts(Collection[i]);
        printf("%s\n\n", Collection[i]);
    }
    char *string = "mul(999,999)";
    int size = strlen(string);
    printf("Size: %d", size);
}
