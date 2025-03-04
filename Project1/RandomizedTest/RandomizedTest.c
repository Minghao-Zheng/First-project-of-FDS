#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../HeaderFiles/Algorithms.h"

int main() {
    /*  N is the quantity of the items.
        a points to the array of all the items. 
        c records the sum. */
        int N = 100000;
        elementType *a;
        elementType c;

        a = (elementArray) malloc(N * sizeof(elementType));
        for (int i = 0; i < N; i++) {
            /*  Generate a truly random number as a[i], 
                which is no larger than V. */
            srand((unsigned)time(NULL));
            a[i] = rand() % N + 1;
        }
        /*  Generate a random number as c, which is no larger than 2V. */
        srand((unsigned)time(NULL));
        c = rand() % (2 * N) + 1;

        
        
        /*  Run the algorithm1 or algorithm2.
            Compare the quantities of the pairs. */
        
           
        int quan1 = algorithm1(N, a, c, 0);
            
        int quan2 = algorithm2(N, a, c, 0);
        
        /*  If the quantities are equal, than the algorithms are compatible. */
        if (quan1 == quan2) {
            printf("The two algorithms are compatible.\n");
        } else {
            printf("Oops! There must be some problems.\n");
        }

        free(a);
}