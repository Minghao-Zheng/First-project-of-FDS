#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/Algorithms.h"

int main() {
    int sign;
    scanf("%d", &sign);

    /*  N is the quantity of the items.
        a points to the array of all the items. 
        c records the sum. */
    int N;
    elementType *a;
    elementType c;
    /*  If sign equals 1, then use algorithm 1.
        If 2, then use algorithm 2. 
        If other digits, then display error messages. */
    if (sign == 1) {
        scanf("%d", &N);
        
        a = (elementArray) malloc(N * sizeof(elementType));
        for (int i = 0; i < N; i++) {
            scanf("%d", a + i);
        }
        scanf("%d", &c);
        /*  The last sign 1 means we can print out the result. */
        algorithm1(N, a, c, 1);
        /*  Free the array. */
        free(a);

    } else if (sign == 2) {
        scanf("%d", &N);

        a = (elementArray) malloc(N * sizeof(elementType));
        for (int i = 0; i < N; i++) {
            scanf("%d", a + i);
        }
        scanf("%d", &c);
        /*  The last sign 1 means we can print out the result. */
        algorithm2(N, a, c, 1);

        free(a);
        
    } else {
        printf("Error! Using illegal sign.\n");
    }
    
}