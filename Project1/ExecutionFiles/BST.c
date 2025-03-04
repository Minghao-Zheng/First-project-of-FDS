#include <stdio.h>
#include <stdlib.h>
#include "../HeaderFiles/BST.h"

/*  Create a node that contains the given item. */
ptrTreeNode createNode(elementType i) {
    ptrTreeNode node = (ptrTreeNode) malloc(sizeof(treeNode));
    node->item = i;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* Add the item into the given BST, with recursion.*/
BST add(BST Tree, elementType i) {
    /*  Create a node that contains the item.*/
    ptrTreeNode node = createNode(i);

    if (Tree == NULL) {
        /*  When we encounter the empty node,
            fill the space with the node we've created. */
        Tree = node;
    } else {
        if (Tree->item == i) {
            /*  If the node's item is equal to the given item,
                do nothing. */
        } else if (Tree->item > i) {
            /*  If the node's item is less than the given item,
                peek into the left subtree. */
            Tree->left = add(Tree->left, i);
        } else {
            /*  If the node's item is larger than the given item,
                peek into the right subtree. */
            Tree->right = add(Tree->right, i);
        } 
    }
    /*  At last, the new BST add a item in a proper space.  */
    return Tree;
}
/*  Traverse the tree to get a, find if c - a exist in the tree. 
    Notice that Tree itself is a node, 
    so we put the tree (for find b), node (to traverse a) and sum into the function.
    The function returns the number of a and c - a.
    Implement the function with recursion. */
int find(BST Tree, ptrTreeNode node, elementType sum, int mode) {
    if (node != NULL) {
        elementType a = node->item;
        /*  Check out if c - a can be found in the Tree. 
            To avoid repetation, we assume that a <= b. */

        /*  "found" records if a and c - a appear in the tree. 
            "mode" records if we want to print out. */
        int found = 0;  
        if (a * 2 <= sum) {
            found = search(Tree, sum - a);
            if (found == 1 && mode == 1) {
                printf("%d + %d = %d\n", a, sum - a, sum);
            }
        }
        
        /*  Peek into the left subtree to traverse. 
            define leftFound to showcase if the left subtree has a + b = c. */
        int leftFound = find(Tree, node->left, sum, mode);
        /*  Peek into the right subtree to traverse. 
            define leftFound to showcase if the left subtree has a + b = c. */
        int rightFound = find(Tree, node->right, sum, mode);
        /*  The tree has a + b that equals to c has the same meaning as 
            The current node has a that c - a is in the tree,
            or the left subtree has a, or the subtree has. */
        return found + leftFound + rightFound;
    }
    /*  If the node is NULL, we can't find anything. */
    return 0;
}
/*  Find the if the b occurs in the Tree, with binary search(recursion). 
    Returns 1 if b occurs, 0 if not. */
int search(BST Tree, elementType b) {
    /*  Tree == NULL means we encounter the empty node,
        which indicates that we don't find b. */
    if (Tree == NULL) {
        return 0;
    }
    if (b == Tree->item) {
        /*  We find out b in the root, so return 1. */
        return 1;
    } else if (b < Tree->item) {
        /*  If b is less then root's item, peek into the left side. */
        return search(Tree->left, b);
    } else {
        /*  If b is larger then root's item, peek into the right side. */
        return search(Tree->right, b);
    }
}

/*  Free the memory of the BST, with recursion. */
void freeTree(BST Tree) {
    if (Tree == NULL) {
        return;
    } 
    /*  Free the left subtree. */
    freeTree(Tree->left);
    /*  Free the right subtree. */
    freeTree(Tree->right);
    free(Tree);
}