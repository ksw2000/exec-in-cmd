#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"advance.h"

double exec_in_cmd(char* str){
    clock_t timer;
    timer = clock();
    system(str);
    timer = clock() - timer;

    return (double)timer / CLOCKS_PER_SEC;
}

int main(int argc, char** argv){
    // argv[1] get path (end without \)
    // argv[2] get filename (not including extension)   or --run
    // argv[3] get filename extension (start with .)    or command (for running directly)
    // argv[4] 1: if use advance mode , 0: else         or filename + fileExtension
    // argv[5]
        // ASM                  output folder (end with \)
        // C,C++,C#,Java        output folder (end with \)
        // Python               python interpreter (python or python3)
    // argv[6]
        // asm                  flag (win64 | win32)
        // java                 package name (java)

    //Get disk name
    int i, j;
    for(i = 0; (i < strlen(argv[1])) && (argv[1][i] != ':'); i++);

    char* diskName = calloc(i+2, sizeof(char));

    for(j=0; j<i+1; diskName[j] = argv[1][j], j++);
    diskName[j] = '\0';

    // Declare some variables
    int    exitFlag     = 0;
    double compile_time = 0.0;
    double exec_time    = 0.0;
    double total_time   = 0.0;
    char   *str         = calloc(65535, sizeof(char));
    char   *str2        = calloc(65535, sizeof(char));

    // Initialize str
    sprintf(str, "%s & cd \"%s\"", diskName, argv[1]);

    // Run command directly
    if(!strcmp(argv[2], "--run")){
        sprintf(str, "%s & cd %s & %s \"%s\"", diskName, argv[1], argv[3], argv[4]);
        goto EXEC;  // Skip argv[5], argv[6], argv[7] ... simple mode not support
    }

    int advance = (strcmp(argv[4], "1") == 0)? 1 : 0;
    if(advance) goto EXEC;   // Must after initializing str

    if(!strcmp(argv[3], ".asm")){
        //Compile
        sprintf(str, "%s & chcp 65001 & md \"%s\" & cls & nasm -f %s \"%s.asm\" -o \"%s%s.obj\"",\
                str, argv[5], argv[6], argv[2], argv[5], argv[2]);
    }else if(!strcmp(argv[3], ".java")){
        //Compile
        char backFolder[128];
        if(strcmp(argv[6], "0")){
            strcpy(backFolder, "..\\");
            int i;
            for(i=0; i<strlen(argv[6]); i++){
                if(argv[6][i] == '.'){
                    strcat(backFolder, "..\\");
                }
            }

            sprintf(str, "%s & md \"%s%s\" & cls & javac -encoding UTF-8 -d %s%s -classpath %s%s %s.java",\
                    str, backFolder, argv[5] , backFolder, argv[5], backFolder, argv[5], argv[2]);
        }else{
            sprintf(str, "%s & md \"%s\" & cls & javac -encoding UTF-8 -d %s -classpath %s %s.java",\
                    str, argv[5], argv[5], argv[5], argv[2]);
        }

        compile_time = exec_in_cmd(str);
        strcpy(str2, str);

        //Run
        if(strcmp(argv[6], "0")){
            sprintf(str, "%s & cd \"%s\" & cd \"%s\" & cd \"%s\" & java %s.%s",\
                    diskName, argv[1], backFolder, argv[5], argv[6], argv[2]);
        }else{
            sprintf(str, "%s & cd \"%s\\%s\" & java %s",\
                    diskName, argv[1], argv[5], argv[2]);
        }
    }else if(!strcmp(argv[3],".kt")){
        //Compile
        sprintf(str, "%s & md \"%s\" & cls & kotlinc %s.kt -include-runtime -d \"%s%s.jar\"",\
                str, argv[5], argv[2], argv[5], argv[2]);
        compile_time = exec_in_cmd(str);
        strcpy(str2,str);

        //Run
        sprintf(str, "%s & cd \"%s\\%s\" & java -jar \"%s.jar\"",\
                diskName, argv[1], argv[5], argv[2]);
    }else if(!strcmp(argv[3],".c") || !strcmp(argv[3],".cpp")){
        //Compile
        sprintf(str, "%s & chcp 65001 & md \"%s\" & cls &", str, argv[5]);
        sprintf(str, "%s %s", str, (!strcmp(argv[3],".c"))? "gcc" : "g++");
        sprintf(str, "%s \"%s%s\" -O2 -o \"%s%s.exe\"", str, argv[2], argv[3], argv[5], argv[2]);
        compile_time = exec_in_cmd(str);

        //Run
        strcpy(str2,str);
        sprintf(str,"%s & \"%s\\%s%s.exe\"", diskName, argv[1], argv[5], argv[2]);
    }else if(!strcmp(argv[3],".cs")){
        //Compile
        sprintf(str, "%s & md \"%s\" & cls & mcs -out:\"%s%s.exe\" \"%s.cs\"",\
                str, argv[5], argv[5], argv[2], argv[2]);
        compile_time = exec_in_cmd(str);

        //Run
        strcpy(str2,str);
        sprintf(str, "%s & \"%s\\%s%s.exe\"", diskName, argv[1], argv[5], argv[2]);
    }else if(!strcmp(argv[3], ".rs")){
        //Compile
        sprintf(str, "%s & rustc \"%s.rs\" --out-dir \"%s\\\"",\
                str, argv[2], argv[5]);
        compile_time = exec_in_cmd(str);

        //Run
        strcpy(str2,str);
        sprintf(str,"%s & \"%s\\%s%s.exe\"", diskName, argv[1], argv[5], argv[2]);
        // Use simple command
    }else if(!strcmp(argv[3], ".py")){
        sprintf(str, "%s & %s \"%s%s\"", str, argv[5], argv[2], argv[3]);
    }else if(!strcmp(argv[3], ".go")){
        sprintf(str, "%s & go run \"%s%s\"", str, argv[2], argv[3]);
    }else{
        fprintf(stderr, "Invalid extension\n");
        exit(1);
    }

EXEC:
    if(advance){
        if(!strcmp(argv[3], ".c") || !strcmp(argv[3], ".cpp")){
            exitFlag = c_advance(str, str2 ,argv, &compile_time);
        }else if(!strcmp(argv[3], ".py")){
            exitFlag = py_advance(str, argv);
        }else if(!strcmp(argv[3], ".go")){
            exitFlag = go_advance(str, argv);
        }
    }

    exec_time = exec_in_cmd(str);
    if(compile_time>0){
        total_time=compile_time+exec_time;
        printf("\n--------------------------------\n");
        printf("%-12s%s\n%-12s%s\n\n",\
               "Compiling:", str2, "Running: ", str);
        printf("%-12s%.4f s\n%-12s%.4f s\n%-12s%.4f s\n",\
               "Compiling:", compile_time, "Executing:", exec_time, "Total:", total_time);
        if(argc>7){
            if(strcmp(argv[6], "0")){
                printf("Package:\t\t%s\n", argv[6]);
            }
        }
        printf("\n");
    }else{
        printf("\n--------------------------------\n");
        printf("Command:\n%s\n\n",str);
        printf("Total Time: %.4f s\n\n",exec_time);
    }

    if(!exitFlag){
        system("pause");
    }
	return 0;
}
