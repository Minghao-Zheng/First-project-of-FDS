#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include "Derivative.h"
#include "Stack.h"
#include "ExpressionTree.h"

int main() {
    /*  The main function to implement the derivative. */
    printf("Please type in the function you want to derive:\n");
    char s[MAXLEN];
    scanf("%s", s);
    operation(s);
    printf("Press enter to exit...\n");
    char enter = 0;
    while (enter != '\r' && enter != '\n') { 
        enter = getch(); 
    }
    return 0;
}