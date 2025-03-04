#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/AList.h"

/*  Create an AList with maxsize n. */
ptrToAList createList(int n) {
    /*  Create a pointer to an array and an AList */
    elementType *A = (elementType*) malloc(n * sizeof(elementType));
    ptrToAList list = (ptrToAList) malloc(sizeof(AList));
    /*  Initialize the content of AList. */
    list->a = A;
    list->size = 0;
    return list;
}
/*  Add item to the last of the AList. */
void addLast(ptrToAList list, elementType item) {
    /*  Add 1 to the size of the AList.
        Add the item to the last of AList. */
    int size = list->size;
    elementArray A = list->a;
    A[size] = item;
    list->size = ++size;
}
/*  When we use mergeSort, we conceal the size of it.
    But to implement it in detail, we need the helper function.*/
void mergeSort(ptrToAList list) {
    int r = myMergeSort(list->a, list->size);
    /*  Update the size because of the repeatition. */
    list->size = r;
}
/*  Implement the merge sort, by recursion. */
int myMergeSort(elementArray array, int size) {
    /*  Make the array be cut by half. */
    int cut;
    int leftsize = size / 2;
    cut = leftsize;
    int rightsize = size - leftsize;

    /*  If size == 1, stop the sort. */
    if (size == 1) {
        return 1;
    }
    /*  Adopting divide and conquer algorithm.
        sort the left and right array seperately. */
    rightsize = myMergeSort(array + leftsize, rightsize);
    leftsize = myMergeSort(array, leftsize);

    /*  Merge two ordered array together. */

    /*  To keep it robust, we create an array that copy
        the left part and the right part seperately. */
    elementArray left = (elementArray) malloc(leftsize * sizeof(elementType));
    elementArray right = (elementArray) malloc(rightsize * sizeof(elementType));

    for (int i = 0; i < leftsize; i++) {
        left[i] = array[i];
    }
    for (int i = 0; i < rightsize; i++) {
        right[i] = array[i + cut];
    }
    /*  Two pointers indicate the item we're thinking about. 
        The arrayPointer indicate the current position of the original array.*/
    int leftPointer, rightPointer, arrayPointer;
    arrayPointer = leftPointer = rightPointer = 0;

    /*  While two pointers are in the middle of the left/right part. */
    while (leftPointer < leftsize && rightPointer < rightsize) {
        /*  If the left item is less than or equal to the right item,
            add the left item to the original array. 
            Then make the left pointer and the array pointer increase.
            Vice versa. */
        if (left[leftPointer] < right[rightPointer]) {
            array[arrayPointer++] = left[leftPointer++];
        } else if (left[leftPointer] > right[rightPointer]) {
            array[arrayPointer++] = right[rightPointer++];
        } else {
            array[arrayPointer++] = left[leftPointer++];
            rightPointer++;
        }
    }

    /*  Now, there are at most one part(left or right) is not be completely considered.
        So we just need to add the remainder to the original array. */
    if (leftPointer == leftsize) {
        while (rightPointer < rightsize)
            array[arrayPointer++] = right[rightPointer++];
    } else {
        while (leftPointer < leftsize)
            array[arrayPointer++] = left[leftPointer++];
    }
    /*  Free the left and right pointer. */
    free(left);
    free(right);
    /*  Return the new array's size. */
    return arrayPointer;
}

/*  Find the a and b in the list so that a+b=c.
    If mode == 1, type "a + b = c" when a and b is found, 
    or "Not found!" if not. 
    Return the quantity of (a, b) pairs. */
int findOut(elementType c, ptrToAList list, int mode) {
    /*  Records if we can find a and b. */
    int num = 0;
    /*  Take the array and size out seperately. */
    elementArray array = list->a;
    int size = list->size;
    /*  curA records the current position of a,
        curB records the current position of b. */
    int curA, curB;
    curA = 0;
    curB = size - 1;

    /*  Assume that a <= b, so a * 2 <= c
        Traverse the array for a,
        from smallest item until a * 2 > c. */
    while (array[curA] * 2 <= c) {
        elementType a = array[curA];
        /*  When a increase, b decrease.
            So when curA increase, curB just decrease.
            When a traverse the array, if b is in the array, b traverse the array either. 
            The flash() function flashes the curB 
            to make a[curB] + a just smaller or equal to c,
            and indicates if b occurs in the array. */
        int found = flash(&curB, array, c - a);
        if (found == 1) {
            if (mode == 1) {
                printf("%d + %d = %d\n", a, c - a, c);
            }
            num += 1;
        }
        /*  Increase the index of a. */
        curA++;
    }
    /*  Statement == 0 means that we can't find. */
    if (!num && mode == 1) {
        printf("Not found!\n");    
    }
    return num;
}

/*  flashes the curB 
    to make a[curB] + a just smaller or equal to c.
    Return 1 if b occurs in the array, return 0 if not. */
int flash(int *cur, elementArray array, elementType b) {
    /*  deliver the pointer just to change it through function. */
    int curB = *cur;
    /*  Decrease the curB when array[curB] > b */
    while (array[curB] > b) {
        curB--;
    }
    /*  Transmit curB back to the pointer*/
    *cur = curB;
    if (array[curB] == b) {
        return 1;
    } else {
        return 0;
    }
}
/*  Free the memory of the list. */
void freeAList(ptrToAList list) {
    free(list->a);
    free(list);
}
