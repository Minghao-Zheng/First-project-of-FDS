#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "ExpressionTree.h"
#include "Stack.h"

void test(char *, char *);
char *preOrderT(ETree t);
int main() {
    //  Test the simplest case.
    char s1[10] = "a+b*c-d";
    char o1[10] = "-+a*bcd";
    //  Another simple case.
    char s2[20] = "a/b^c";
    char o2[10] = "/a^bc";
    //  Test a simple case with real numbers.
    char s3[10] = "2^a+b";
    char o3[10] = "+^2ab";
    //  Test the larger case.
    char s4[50] = "(a+b)/c^d*e-ha*ha^xy^zz";
    char o4[50] = "-*/+ab^cde*ha^^haxyzz";

    //  The append case, shows whether some other functions works well.
    char s5[50] = "ln(a)^log(aa,bb)-pow(exp(a)/(cos(aa)+bb),bb)";
    char o5[50] = "-^lnalogaabbpow/expa+cosaabbbb";
    //  Test the ilegal case.
    char s6[10] = "a++b--/c";
    char o6[10] = "";
    //  Test the ilegal case of variables.
    char s7[15] = "2a^bcd+p3f";
    char o7[15] = "";
    //  Test the case with -.
    char s8[10] = "-a+b-c";
    char o8[10] = "-+-0abc";

    //  Test all the samples.
    test(s1, o1);
    test(s2, o2);
    test(s3, o3);
    test(s4, o4);
    test(s5, o5);
    test(s6, o6);
    test(s7, o7);
    test(s8, o8);
  
}

/*  Test if the input s has the relative output o. */
void test(char *s, char *o) {
    ETree t = putinET(s);   /*  Put the string into the expression tree. */
    /* Get the string out of the preorder traversal of the expression tree. */
    char *output = preOrderT(t); 
    /*  Whether the output string is as expected or not,
        show the outcome. */
    if (strcmp(output, o) == 0) {
        printf("The case %s works well.\n", s);
    } else {
        printf("Oops, there must be some problems with the case %s and it returns %s\n"
            , s, output);
    }

}
/*  Preorder traversal, with recursion. */
char *preOrderT(ETree t) {
    char *s;
    s = (char *)malloc(sizeof(char) * 50);
    s[0] = '\0';
    if (t != NULL) {
        /*  Sequencially add the node's item, its left and its right to the string. */
        strcat(s, t->a);
        strcat(s, preOrderT(t->left));
        strcat(s, preOrderT(t->right));
    }
    return s;
}