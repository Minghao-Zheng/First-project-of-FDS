#ifndef __EX_TREE__
#define __EX_TREE__


#include "Variables.h"

/*  Put a in-order expression into the expression tree. */
ETree putinET(char *);
/*  Convert a in-order expression into the post order expression.
    And make every item be concealed in the array of TreeNode. */
ETree *inToPost(char *);
/*  A function to operate special functions. */
int speFuntoSt(Stack, char *);
/*  Put a operator in the function and return its precedence. */
int pre(char);
/*  Test if the string is a binary operator. */
int biop(char *);
/*  Test if the string is a binary operator. */
int unop(char *);
/*  Add the variables to the vtree. */
VTree add(char *, VTree);
/*  Free the ETree. */
void freeETree(ETree);

#endif