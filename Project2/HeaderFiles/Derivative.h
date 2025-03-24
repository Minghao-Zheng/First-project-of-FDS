#ifndef __DIR__
#define __DIR__

#include "Variables.h"
/*  The method to implement differentiation function. */
void operation(char *);
/*  We use the expression tree and the variable tree to implement the function. */
void implement(ETree, VTree);
/*  Differentiate with a particular variable. */
void derivative(ETree, char *);
/*  Print the infix expression with the expression tree. */
void print(ETree);
/*  Free all the node in the VTree. */
void freeVTree(VTree);

#endif