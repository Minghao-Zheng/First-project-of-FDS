#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Derivative.h"
#include "ExpressionTree.h"
#include "Stack.h"
/*  Put a string into the function, and get the result. */
void operation(char *s) {
    /*  First, put infix expression into expression tree,
        and get all the variables. */
    ETree t = putinET(s);

    if (t == NULL) {
        /*  If t == NULL, then there must be something strange occurs,
            just complain about it. */
        fprintf(stderr, "Illegal expression\n");
        exit(3);
    }
    /*  Then, implement the function by using another method. */
    implement(t, variables);  
    /*  At last, free the tree and the variable. */
    freeETree(t);
    freeVTree(variables);

}
/*  We use the expression tree and the variable tree to implement the function. 
    By recursion. */
void implement(ETree t, VTree v) {
    if (v == NULL) {
        /*  If v = NULL, then return to its root. */
        return ;
    } else {
        /*  v is not NULL, just traverse its left, then itself, then its right before go to its root. */
        implement(t, v->vleft);
        /*  We find the proper value and do derivative. */
        printf("%s: ", v->var);
        derivative(t, v->var);
        printf("\n");
        implement(t, v->vright);
    }
}
/*  Derivative by pre-order traversal. */
void derivative(ETree t, char *var) {
    /*  We use derivative to records the form of derivative,
        and use print to records the form of the original function. */
    if (!strcmp(t->a, "+")) {
        /*  If the operator is +. 
            The rule is derive both part respectively. */
        printf("(");
        derivative(t->left, var);
        printf("+");
        derivative(t->right, var);
        printf(")");
    } else if (!strcmp(t->a, "-")) {
        /*  If the operator is +. 
            The rule is same as +. */
        printf("(");
        derivative(t->left, var);
        printf("-");
        derivative(t->right, var);
        printf(")");
    } else if (!strcmp(t->a, "*")) {
        /*  If the operator is *.
            The rule is a * b -> a * b' + b * a'. */
        printf("(");
        derivative(t->left, var);
        printf("*");
        print(t->right);
        printf("+");
        print(t->left);
        printf("*");
        derivative(t->right, var);
        printf(")");
    } else if (!strcmp(t->a, "/")) {
        /*  If the operator is /,
            the rule is a/b -> (a'b-b'a)/b^2*/
        printf("((");
        derivative(t->left, var);
        printf("*");
        print(t->right);
        printf("-");
        print(t->left);
        printf("*");
        derivative(t->right, var);
        printf(")/");
        print(t->right);
        printf("^2)");
    } else if (!strcmp(t->a, "^") || !strcmp(t->a, "pow")) {
        /*  The rule is :
            a^b -> a^b*(a'*b/a+b'*ln(a)) */
        printf("(");
        print(t->left);
        printf("^");
        print(t->right);
        printf("*(");
        derivative(t->left, var);
        printf("*");
        print(t->right);
        printf("/");
        print(t->left);
        printf("+");
        derivative(t->right, var);
        printf("*ln(");
        /*  For t->left has its own (), so we don't bother to add (). */
        print(t->left);
        printf(")))");

    } else if (!strcmp(t->a, "exp")) {
        /*  The rule is :
            exp(a) -> exp(a)*a'. */
        printf("(exp(");
        print(t->left);
        printf(")*");
        derivative(t->left, var);
        printf(")");
    } else if (!strcmp(t->a, "ln")) {
        /*  The rule is :
            ln(a) -> a'/a. */
        printf("(");
        derivative(t->left, var);
        printf("/");
        print(t->left);
        printf(")");
    } else if (!strcmp(t->a, "log")) {
        /*  The rule is :
            log(a,b) -> (b'ln(a)/b-a'ln(b)/a)/(lna)^2. */
        printf("((");
        derivative(t->right, var);
        /*  Like what we've learnt in ^. */
        printf("*ln(");
        print(t->left);
        printf(")/");
        print(t->right);
        printf("-");
        derivative(t->left, var);
        printf("*ln(");
        print(t->right);
        printf(")/");
        print(t->left);
        printf(")/ln(");
        print(t->left);
        printf(")^2)");
    } else if (!strcmp(t->a, "sin")) {
        /*  The rule is :
            sin(a) -> cos(a) * a'*/
        printf("(cos(");
        print(t->left);
        printf(")*");
        derivative(t->left, var); 
        printf(")");  
    } else if (!strcmp(t->a, "cos")) {
        /*  cos(a) -> -sin(a) * a'*/
        printf("-(sin(");
        print(t->left);
        printf(")*");
        derivative(t->left, var);
        printf(")");
    } else if (!strcmp(t->a, "tan")) {
        /*  tan(a) -> sec(a) ^ 2 * a'. */
        printf("(sec(");
        print(t->left);
        printf(")^2*");
        derivative(t->left, var);
        printf(")");
    } else if (!strcmp(t->a, var)) {
        printf("1");
    } else {
        printf("0");
    }
}
/*  Print the infix expression from the expression tree. */
void print(ETree t) {
    char *s = t->a;
    /*  If the string is a operand, then just print out it. */
    if (!biop(s) && !unop(s)) {
        printf("%s", s);
    } else if (biop(s) && strcmp(s, "log") && strcmp(s, "pow")) {
        /*  If the string is a binary operator,
            then the form is (left operator right)
            except for log and pow. */
        printf("(");
        print(t->left);
        printf("%s", s);
        print(t->right);
        printf(")");
    } else if (unop(s)) {
        /*  If the string is a unary operator,
            then the form is (unary(left))*/
        printf("(");
        printf("%s(", s);
        print(t->left);
        printf("))");
    } else {
        /*  If the string is log or pow,
            then the form is operator(left,right). */
        printf("(%s(", s);
        print(t->left);
        printf(",");
        print(t->right);
        printf(")");
    }
}
/*  Free the VTree, with recursion. */
void freeVTree(VTree v) {
    if (v == NULL) {
        /*  If VTree is NULL, do nothing. */
        return ;
    } else {
        /*  Free all the nodes by post-order traversal. */
        freeVTree(v->vleft);
        freeVTree(v->vright);
        free(v);
    }
}