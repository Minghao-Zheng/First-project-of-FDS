#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/Algorithms.h"

/*  This is a large scale test that test the extreme case. 
    And, it has repetition. */

int main() {
    int a[100000] = {0};
    int n = 100000;
    int c = 5086;

    /*  We assume that the items are all the odd numbers between 1 and 50086*/
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            a[i] = i % 5086 + 1;
        } else {
            a[i] = i % 5086;
        }
    }
    /*  Records the quantity of the pairs. */
    int found = algorithm1(n, a, c, 0);
    /*  Say, a(an odd), and 50086 - a. */
    if (found == 1272) {
        printf("Algorithm1 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm1.\n");
    }   
    /*  The same as algorithm1. */
    int foundOut = algorithm2(n, a, c, 0);
    if (foundOut == 1272) {
        printf("Algorithm2 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm2.\n");
    }
    /*  When c = 0, there can't found a single pair. */
    c = 0;
    int notFound = algorithm1(n, a, c, 0);
    if (notFound == 0) {
        printf("Algorithm1 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm1.\n");
    }
    int notFoundOut = algorithm2(n, a, c, 0);
    if (notFoundOut == 0) {
        printf("Algorithm2 works well.\n");
    } else {
        printf("Oops, there must be some problems with algorithm2.\n");
    }
}

/*  You may find it using too much time operating, 
    that's maybe because the time complexity of algorithm1 is similar to O(n^2),
    the worst case. */