#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/Algorithms.h"

/*  This is a simple test just for the fundamental correctness. */

int main() {
    int a[8] = {2, 3, 5, 7, 11, 13, 15, 16};
    int c = 18;
    /*  Records the quantity of the pairs. */
    int found = algorithm1(8, a, c, 1);
    /*  Say, 2 + 16, 3 + 5, 5 + 13, 7 + 11. */
    if (found == 4) {
        printf("Algorithm1 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm1.\n");
    }
    /*  The same as algorithm1. */
    int foundOut = algorithm2(8, a, c, 1);
    if (found == 4) {
        printf("Algorithm2 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm2.\n");
    }
    /*  When c = 33, there can't found a single pair. */
    c = 33;
    int notFound = algorithm1(8, a, c, 1);
    if (notFound == 0) {
        printf("Algorithm1 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm1.\n");
    }
    int notFoundOut = algorithm2(8, a, c, 1);
    if (notFoundOut == 0) {
        printf("Algorithm2 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm2.\n");
    }
}