#include <stdio.h>
#include "../HeaderFiles/BST.h"

/*  Take advantage of binary search tree to solve this problem.
    N records the quantity of the integers. 
    a records the array which contains our items.
    c records the sum.
    mode records whether we want to print. */
int algorithm1(int N, elementType *a, elementType c, int mode) {
    BST Tree = NULL;
    /*  Construct a binary search tree to store the positive number we input. */ 
    for (int i = 0; i < N; i++) {

        /*  Every item comes, add it to our BST. */
        Tree = add(Tree, a[i]);
    }

    /*  Traverse all the members in the BST as a. 
        With every a, find c - a in the BST. 
        if we can find a and c - a in the tree, found is 1.
        if not, found is 0. 
        "mode" indicates whether we want to print out the result. */   
    int found = find(Tree, Tree, c, mode);

    /*  If found is 0 and mode is 1, print out "Not found!" */
    if (found == 0 && mode == 1) {
        printf("Not found!\n");  
    }

    freeTree(Tree);

    return found;
}