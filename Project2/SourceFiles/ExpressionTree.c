#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ExpressionTree.h"
#include "Stack.h"

/*  Define a global variable to contain all the variables. */
VTree variables = NULL;

ETree putinET(char *s) {
    /*  First, convert the in-order expression to the post-order one. */
    ETree *p = inToPost(s);
    /*  Then, take use of stack to change it to ET. */
    Stack st = createStack();
    /*  We add the item from the post-order expression into the ET. */
    for (int i = 0; i < MAXLEN && p[i] != NULL; i++) {

        if (!biop(p[i]->a) && !unop(p[i]->a)) {
            /*  If the data is not a operator, 
                then push it into the stack. */
            st = push(p[i], st);
        } else if (biop(p[i]->a)) {
            /*  If the data is a binary operator,
                then pop out the first two operands and add them
                to the left and right of the tree. */
            ETree operand2 = pop(st);
            ETree operand1 = pop(st);
            /*  If there exists a NULL, then there must be something wrong. */
            if (operand1 == NULL || operand2 == NULL) {
                return NULL;
            }
            p[i]->left = operand1;
            p[i]->right = operand2;
            st = push(p[i], st);
        } else {
            /*  If the data is a unary operator,
                then pop out the top item and add it 
                to the left of the tree. */
            ETree operand = pop(st);
            p[i]->left = operand;
            /*  If there exists a NULL, then there must be something wrong. */
            if (operand == NULL) {
                freeStack(st);
                return NULL;
            }
            st = push(p[i], st);
        }

    }
    ETree expressionTree = pop(st);
    if (checkempty(st) != 0) {
        /*  If the stack is not empty, then return NULL. */
        freeStack(st);
        return NULL;
    }
    freeStack(st);
    return expressionTree;

}

ETree *inToPost(char *s) {
    /*  r is the array we want to contain every pointer to the node. */
    ETree *r = (ETree *)malloc(sizeof(ETree) * MAXLEN);
    Stack st = createStack();
    /*  num records the current number of items that is in the array. */
    int num = 0;
    /*  State records if there are special function:
        sin, cos, tan, log, ln, pow, exp. */
    int state = 0;

    for (int i = 0; i < strlen(s); ) {
        if (s[i] == '(' && state) {
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            /*  If the item is '(', and there is a special function before it,
                then just put it into the stack. */
            p->a = "(";
            st = push(p, st);
            i++;
            /*  At last, let state back to 0. */
            state = 0;
        } else if (s[i] == '(' && !state) {
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            p->a = "(";
            /*  If the '(' is not right after a special function,
                then put a NULL item into the stack before put the '(' into it. */
            ETree q = (ETree) malloc(sizeof(TreeNode));
            q->left = q->right = NULL;
            q->a = NULL;
            st = push(q, st);
            st = push(p, st);
            i++;
        } else if (s[i] == ')') {
            /*  When we encounter ')', just pop twice, 
                no matter what the exactly the stack contains. */
            ETree q;
            while(strcmp((q = pop(st))->a, "(")) {
                r[num++] = q;
            }
            /*  At last, pop the thing before '(' out,
                If the item is NULL, do nothing,
                if the item is not NULL, add it to the r. */
            q = pop(st);
            if (q->a != NULL) {
                r[num++] = q;
            }
            i++;
        } else if (!strncmp(s + i, "sin(", 4)) {
            /*  If the function sin occurs. */
            state = speFuntoSt(st, "sin");
            i += 3;  
        } else if (!strncmp(s + i, "cos(", 4)) {
            /*  If cos occurs. */
            state = speFuntoSt(st, "cos");
            i += 3;
        } else if (!strncmp(s + i, "tan(", 4)) {
            /*  If tan occurs. */
            state = speFuntoSt(st, "tan");
            i += 3;
        } else if (!strncmp(s + i, "ln(", 3)) {
            /*  If ln occurs. */
            state = speFuntoSt(st, "ln");
            i += 2;
        } else if (!strncmp(s + i, "log(", 4)) {
            /*  If log occurs. */
            state = speFuntoSt(st, "log");
            i += 3;
        } else if (!strncmp(s + i, "pow(", 4)) {
            /*  If pow occurs. */
            state = speFuntoSt(st, "pow");
            i += 3;
        } else if (!strncmp(s + i, "exp(", 4)) {
            /*  If exp occurs. */
            state = speFuntoSt(st, "exp");
            i += 3;
        } else if (s[i] == ',') {
            /*  When ',' occurs, then there can't be any other '(' 
                after 'log(' or 'pow(' before the ',' in the stack. 
                So feel free to pop out all the items before '('. */
            ETree q;
            while(strcmp((q = pop(st))->a, "(")) {
                r[num++] = q;
            }
            /*  At last, for we pop out the '(', we need to push it back. */
            st = push(q, st);
            i++;
        } else if (s[i] == '^' || s[i] == '*' || s[i] == '/' || s[i] == '+') {
            /*  ^, *, / and + have the same rule of pushing into the stack. 
                However - has some strange cases because it can be a part of negtive numbers. */
            while (checkempty(st) && pre(s[i]) <= pre(gettop(st)[0])) {
                /*  While the top item has the same or larger precedence than the input item,
                    pop them out. */
                r[num++] = pop(st);
            }
            /*  At last, push the item in. */
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            /*  Use str to contain the operator. */
            char *str = (char *) malloc(sizeof(char) * 2);
            strncpy(str, s + i, 1);
            str[1] = '\0';
            p->a = str;
            st = push(p, st);
            i++;
        } else if (s[i] == '-' && i != 0 && s[i-1] != '+' && s[i-1] != '(' 
            && s[i-1] != '*' && s[i-1] != '/' && s[i-1] != '-' && s[i-1] != ',') {
            /*  If the - satisfy the conditions above, then it is the binary operator. 
                The operation is the same as +, * / and ^. */
            while (checkempty(st) && pre(s[i]) <= pre(gettop(st)[0])) {
                /*  While the top item has the same or larger precedence than the input item,
                    pop them out. */
                r[num++] = pop(st);
            }
            /*  At last, push the item in. */
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            p->a = "-";
            st = push(p, st);
            i++;
        } else if (s[i] == '-') {
            /*  If the - doesn't satisfy the conditions, then it is an unary operator. 
                Then deal with it like the other digits. */
            /*  Let -a becomes (0-a). */
            ETree q = (ETree) malloc(sizeof(TreeNode));
            q->left = q->right = NULL;
            q->a = "0";
            r[num++] = q;
            /*  After 0, then deal with the variable or digits after it. */
            i++;
            int ini = i;    // The initial index.
            char *str = (char *) malloc(sizeof(char) * MAXSIZE);  //  The string that contains the variable.
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            /*  Deal with the digits or variable. */
            if (s[i] >= '0' && s[i] <= '9') {
                while (s[i] >= '0' && s[i] <= '9') 
                    i++;
            } else if (s[i] >= 'a' && s[i] <= 'z') {
                while (s[i] >= 'a' && s[i] <= 'z') 
                    i++;
            }
            if (i - ini + 1 >= MAXSIZE) {
                /*  If the variable is too long, then complain about it. */
                freeStack(st);
                fprintf(stderr, "Too long variable\n");
                exit(4);
            }
            /*  Put all the sequential digits or variables into the node. */
            strncpy(str, s + ini, i - ini);
            str[i-ini] = '\0';
            p->a = str;
            /*  If the string is a variable, then put it into the set of variables. */
            if (str[0] >= 'a' && str[0] <= 'z') {
                variables = add(str, variables);
            }
            /*  Put the variable into the array without pushing it into the stack. */
            r[num++] = p;
            /*  At last, push '-' into the array. */
            ETree o = (ETree) malloc(sizeof(TreeNode));
            o->left = o->right = NULL;
            o->a = "-";
            r[num++] = o; 
        } else if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= '0' && s[i] <= '9') {
            /*  If the s[i] is a lowercase letter or digits, 
                then find all the lowercase letter after it and copy it to a string. 
                The variable can't be longer than MAXSIZE. */
            int ini = i;    // The initial index.
            char *str = (char *) malloc(sizeof(char) * MAXSIZE);  //  The string that contains the variable.
            /*  Create a node that will be put in r. */
            ETree p = (ETree) malloc(sizeof(TreeNode));
            p->left = p->right = NULL;
            /*  Deal with the digits or variable. */
            if (s[i] >= '0' && s[i] <= '9') {
                while (s[i] >= '0' && s[i] <= '9') 
                    i++;
            } else if (s[i] >= 'a' && s[i] <= 'z') {
                while (s[i] >= 'a' && s[i] <= 'z') 
                    i++;
            }
            if (i - ini + 1 >= MAXSIZE) {
                /*  If the variable is too long, then complain about it. */
                freeStack(st);
                fprintf(stderr, "Too long variable\n");
                exit(4);
            }
            /*  Put all the lowercase letter in a sequence into the node. */
            strncpy(str, s + ini, i - ini);
            str[i-ini] = '\0';
            p->a = str;
            /*  If the string is a variable, then put it into the set of variables. */
            if (str[0] >= 'a' && str[0] <= 'z') {
                variables = add(str, variables);
            }
            /*  Put the variable into the array without pushing it into the stack. */
            r[num++] = p;
        } else {
            /*  If some illegal input occurs, then complain about it. */
            freeStack(st);
            fprintf(stderr, "Illegal input\n");
            exit(2);
        }
    }
    /*  At last, pop out all the items in the stack. */
    while (checkempty(st)) {
        char *topItem = gettop(st);
        if (!biop(topItem)) {
            /*  If the top item is not "+" or "-" or "*" or "/" or "^"
                then there must lies some problems. */
            freeStack(st);
            fprintf(stderr, "Illegal input\n");
            exit(2);
        }
        r[num++] = pop(st);
    }
    /*  Set the last item to be NULL. */
    if (num <= MAXLEN - 1) {
        r[num] = NULL;
    } else {
        /*  If the expression is too long, then complain about it. */
        fprintf(stderr, "Expression too long\n");
        exit(1);
    }
    freeStack(st);
    
    return r;

}
/*  This is a function that can put a special function properly into the stack
    in the process to change in-order expression to post-order expression. */
int speFuntoSt(Stack st, char *fun) {
    
    /*  Create a node that will be put in r. */
    ETree p = (ETree) malloc(sizeof(TreeNode));
    p->left = p->right = NULL;
    p->a = fun;
    /*  For the special function is unary operator, 
        then we need just push it like '('. */
    st = push(p, st);
    /*  Return the state. */
    return 1;
}
/*  Return the precedence by using numbers. 
    The larger number indicates the higher precedence. */
int pre(char s) {
    switch(s) {
        case '^':
        /*  ^ has the highest precedence. */
            return 3;
            break;
        case '*':
        /*  * and / have the same precedence, lower than ^.  */
            return 2;
            break;
        case '/':
            return 2;
            break;
        case '+':
        /*  + and - have the same precedence, lower than *. */
            return 1;
            break;
        case '-':
            return 1;
            break;
        case '(':
        /*  The '(' in the stack has the lowest precedence. */
            return 0;
            break;
        default:
        /*  There must be something fault.*/
            return 100;
    }
}
/*  Test if the string is a binary operator. 
    If not, returns 0. */
int biop(char *s) {
    int k = strcmp(s, "+") && strcmp(s, "-") && strcmp(s, "*") && strcmp(s, "/")
        && strcmp(s, "^") && strcmp(s, "log") && strcmp(s, "pow");
    return (k == 0);
}
/*  Test if the string is an unary operator.
    If not, returns 0. */
int unop(char *s) {
    int k = strcmp(s, "ln") && strcmp(s, "sin") && strcmp(s, "cos")
        && strcmp(s, "tan") && strcmp(s, "exp");
    return (k == 0);
}

VTree add(char *str, VTree v) {
    
    if(v != NULL) {
        if (strcmp(v->var, str) > 0) {
            /*  If the current value is larger than str,
                then peek in the left. */
            v->vleft = add(str, v->vleft);
        } else if (strcmp(v->var, str) < 0) {
            /*  If the current value is smaller than str,
                then peek in the right. */
            v->vright = add(str, v->vright);
        } 
        return v;
    } else {
        char *s = (char *) malloc(sizeof(char) * MAXSIZE);
        strcpy(s, str);
        /*  Create a node that contains the variable. */
        VTree r = (VTree) malloc(sizeof(VNode));
        r->vleft = NULL;
        r->vright = NULL;
        r->var = s; 
        return r;
    }
     
}
/*  Free the ETree, with recursion. */
void freeETree(ETree e) {
    if (e == NULL) {
        /*  If ETree is NULL, do nothing. */
        return ;
    } else {
        /*  Free all the nodes by post-order traversal. */
        freeETree(e->left);
        freeETree(e->right);
        free(e);
    }
}
