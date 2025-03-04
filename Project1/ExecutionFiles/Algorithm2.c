#include <stdio.h>
#include "../HeaderFiles/AList.h"

/*  Take advantage of array list to solve this problem.
    N indicates the quantity of the items. */
int algorithm2(int N, elementType *a, elementType c, int mode) {
    /*  Add the items the users input into the array list. */
    ptrToAList arrayList = createList(N);
    for (int i = 0; i < N; i++) {

        /*  Add the item to the last. */
        addLast(arrayList, a[i]);
    }

    /*  Use merge sort to sort the items in the array. */
    mergeSort(arrayList);

    /*  Find a pair of two integers a, b, so that a+b=c.
        If mode == 1, print the pair. */
    int foundOut = findOut(c, arrayList, mode);

    /*  Free the arraylist and the array. */
    freeAList(arrayList);

    return foundOut;
}