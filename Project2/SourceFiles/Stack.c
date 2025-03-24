#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"
#include "ExpressionTree.h"


/*  The method creates a stack. */
Stack createStack(void) {
    /*  Create a sentinel node to create the stack. */
    Stack sentinel = (Stack) malloc(sizeof(StackItem));
    /*  Initialize the sentinel. */
    sentinel->next = NULL;
    /*  You shouldn't access the sentinel node! */
    char r[50] = "You shouldn't access the sentinel node.";
    /*  Create a node of ETree as the item of the sentinel. */
    ETree s = (ETree) malloc(sizeof(TreeNode));
    s->a = r;
    s->left = s->right = NULL;

    sentinel->data = s;
    return sentinel;
}

/*  The method push a item into the stack. */
Stack push(ETree s, Stack st) {
    /*  Create a node that contains the string. */
    Stack node = (Stack) malloc(sizeof(StackItem));
    node->data = s;
    /*  Link node to the head of the linked list. */
    node->next = st->next;
    st->next = node;

    return st;
}

/*  Pop out the top item of the stack. 
    If the stack is empty, return NULL. */

ETree pop(Stack st) {
    int state = checkempty(st);
    /*  r is the item we need to return. */
    ETree r = NULL;
    /*  If the stack is not emtpy. Then pop out the top item. */
    if (state) {
        Stack h = st->next;
        /*  The head's item is the item we want.  */
        r = h->data;
        st->next = h->next;
        /*  At last, free the first node. */
        free(h);
    }

    return r;

}
/*  Get the top item of the stack. */
char *gettop(Stack st) {    
    if (checkempty(st)) {
        /*  If the stack is not empty, then return the content of the first node. */
        ETree r = st->next->data;
        return r->a;
    } else {
        /*  If the stack is empty, return NULL. */
        return NULL;
    }
}

/*  Check if the stack is empty. If it is not empty, return 1,
    otherwise return 0. */
int checkempty(Stack st) {
    /*  If the stack has only the sentinel node,
        then it's empty. */
    if(st->next == NULL) {
        return 0;
    } else {
        return 1;
    }
}
/*  Free the stack from top to bottom.*/
void freeStack(Stack st) {

    /*  Just free the st for the latter will be return to the 
        operating system. */
    free(st);
    return ;

}

