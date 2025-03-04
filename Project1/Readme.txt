How to run the executive file?
1. If you have VSCode

I'd recommend you to configure in the way below.

Step1: Get the tasks.json, launch.json, c_cpp_properties.json.
        (Please add "C/C++ (gdb) Launch" configuration to your launch.json)
Step2: Create a folder you want to store your .exe files.
Step3:  Configure the tasks.json
        in the "args": [...]
        Delete the original path between "-g" and "-o"
        Add 
            "*.c",
            "-I","...\\HeaderFiles"(The path of HeaderFiles),
            "...\\ExecutionFiles\\**"(The path of ExecutionFiles),
        between "-g" and "-o";
        Take the original path under "-o" with:
        "...(The path of the folder which stores your .exe files)\\${fileBasenameNoExtension}.exe"
Step4:  Configure the launch.json
        in "configuration": [...]
        Find "program": "...", take it with:
        "...(The path of the folder which stores your .exe files)\\${fileBasenameNoExtension}.exe"
        Find "miDebuggerPath": "...", take it with the path of your gdb(peek it by the command line.)
Step5:  Configure the c_cpp_properties.json
        Just add "...(The path of the HeaderFiles)\\**" in the "includePath" under the original path(don't delete it).

However, you can just copy the code and organize it in the way you like.

2. If you don't have VSCode

Just copy the code and organize it in the way you like.



Now you can run the main.c and TimeTesting.c,
in main.c, first input 1 if you want to implement algorithm1, 2 if you want algorithm2.
then input N, N items, and c.
in TimeTesting.c, first input V which indicates the maximum of the input items.
Then input 1 if you want to implement algorithm1, 2 if you want algorithm2.
Then just input N which indicates the scale.
Wait for a moment then it will generate a graph with randomized data.

         
