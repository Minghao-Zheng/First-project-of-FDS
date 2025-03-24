## How to run the code

> *Tip:* Everything was demonstrated on the Windows operating system, so if you are using other operating systems, please find proper way to rewrite what I say.

There are only two parts in the code folder: The HeaderFiles folder and the SourceFiles folder. The executive files are located in the SourceFile folder, and they are "main.c" and "TestExpressionTree.c" respectively.

To run the code :

**Step1**: (Optional) Create a folder to contain the .exe files. (E.x. bin)

**Step2**: You just need to type in `gcc -g -I HeaderFiles SourceFiles/Derivative.c SourceFiles/ExpressionTree.c SourceFiles/Stack.c SourceFiles/main.c -o bin/main.exe` Replace "bin" with the name of the folder you've just created. If you haven't created a folder, than replace the `bin/main.exe` with everything you like to contain the .exe files.

**Step3**: (Optional) If you're curious about some examples I've tested, then type in `gcc -g -I HeaderFiles SourceFiles/ExpressionTree.c Stack.c TestExpressionTree.c -o bin/TestExpressionTree.exe`, this is a file I've used to find out if the infix expression put in the expression tree is right. 

If you're curious about how I implement it, then open the code folder by vscode or other IDEs is welcomed. 

In the main.exe, please input the expression without whitespace, and just use +, -, *, /, ^, sin( ), cos( ), tan( ), pow( ), ln( ), log( ), exp( ), and "," itself in proper style. Otherwise the program will complain about it. The derived expression will be print out in an undigested form.

In the TestExpressionTree.exe, you don't need to do anything.

Hope you enjoy my work.