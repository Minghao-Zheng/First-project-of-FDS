#ifndef __STACKFILE__
#define __STACKFILE__


#include "Variables.h"

/*  Create a stack. */
Stack createStack(void);
/*  Push an item into the stack. */
Stack push(ETree, Stack);
/*  Pop an item out of the stack. */
ETree pop(Stack);
/*  Check if the stack is empty. */
int checkempty(Stack);
/*  Free the stack. */
void freeStack(Stack);
/*  Get the top item if exists. */
char *gettop(Stack);


#endif