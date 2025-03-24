#ifndef __VAR__
#define __VAR__

/*  The MAXLEN records the max size of the expression.
    (The number of the operators and operands) */
#define MAXLEN  1000
/*  The MAXSIZE records the max size of the variable. */
#define MAXSIZE 50

typedef struct node *ETree; //  ETree refers to the tree.

typedef struct node {
    char *a;
    ETree left;
    ETree right;
} TreeNode; //  TreeNode conceals the details to implements the treenode.

/*  We use linked list to implement stack. */

typedef struct list *Stack;
/*  Every data we put into the stack 
    can be converted into a node of expression tree. */
typedef struct list {
    /*  Data */
    ETree data;
    Stack next;
} StackItem;


typedef struct vnode *VTree;    //  VTree refers to the tree of variables.

typedef struct vnode {
    char *var;
    VTree vleft;
    VTree vright;
} VNode;    //  VNode conceals the details to implements the variable nodes.

/*  The extern vtree that contains the variables. */
extern VTree variables;

#endif