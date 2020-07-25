#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

void pause(){
    printf("Press any key to continue...");
    char c = getc(stdin);
}


struct timeval t;

void timerStart(){
    gettimeofday(&t, NULL);
}

unsigned long timerEnd(){
    struct timeval now;
    gettimeofday(&now, NULL);
    return (unsigned long)(now.tv_usec - t.tv_usec);
}

int main(int argc, char** argv){
    //Timecounter
    int i;
    char *cmd, *cmd_compile;
    char *cmd_assemble, *cmd_link;
    struct  timeval  start, end;
    unsigned long compile_time=0, time=0;
    unsigned long assemble_time=0, link_time=0;

    if(!strcmp(argv[1],".asm")){
        /*
            argv[1] type(.asm)
            argv[2] get path      [end without /]
            argv[3] get filename  [without extension]
            argv[4] flag elf64
            argv[5] output folder [end with /]
        */
        //Phase1: Assembler
        cmd          = malloc(65536 * sizeof(char));
        cmd_assemble = malloc(65536 * sizeof(char));
        cmd_link     = malloc(65536 * sizeof(char));
        sprintf(cmd, "cd \"%s\"; mkdir -p \"%s\"; nasm -f %s \"%s.asm\" -o \"%s%s.o\"",\
                argv[2],argv[5],argv[4],argv[3],argv[5],argv[3]);

        timerStart();
        if(system(cmd)==-1){
            fprintf(stderr,"Assembling error\n");
        }
        assemble_time = timerEnd();
        cmd_assemble  = malloc(65536 * sizeof(cmd));
        strcpy(cmd_assemble,cmd);

        //Phase2: Linker
        sprintf(cmd,"cd \"%s/%s\"; ld -s -o \"%s\" \"%s.o\"",argv[2],argv[5],argv[3],argv[3]);
        timerStart();
        if(system(cmd)==-1){
            fprintf(stderr,"Linking error\n");
        }
        link_time = timerEnd();
        strcpy(cmd_link,cmd);

        //Phase3: Run
        sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argv[2],argv[5],argv[3]);
    }else if(!strcmp(argv[1],".java")){
        cmd = malloc(65536 * sizeof(char));
        cmd_compile = malloc(65536 * sizeof(char));
        /*
            argv[1] type(.java)
            argv[2] get this open.c's path
            argv[3] get path      [end without /]
            argv[4] get filename  [without extension]
            argv[5] output folder [end with /]
            argv[6] package name
        */

        //Phase1: Compile
        char* backFolder = malloc(128*sizeof(char));
        if(strcmp(argv[6], "0")){
            strcpy(backFolder,"../");
            int i;
            for(i=0; i<strlen(argv[6]); i++){
                if(argv[6][i] == '.'){
                    strcat(backFolder, "../");
                }
            }
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s%s\" ; javac -encoding UTF-8 -d \"%s%s\" \
                    -classpath \"%s%s\" \"%s.java\"",\
                    argv[3],backFolder,argv[5],backFolder,argv[5],\
                    backFolder,argv[5],argv[4]);
        }else{
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" \
                    -classpath \"%s\" \"%s.java\"",\
                    argv[3],argv[5],argv[5],\
                    argv[5],argv[4]);
        }

        timerStart();
        if(system(cmd)==-1){
            fprintf(stderr,"Java compile error\n");
        }
        compile_time = timerEnd();

        strcpy(cmd_compile,cmd);

        //Phase2: Run
        if(strcmp(argv[6], "0")){
            sprintf(cmd,"cd \"%s\"; cd \"%s\"; cd \"%s\"; java %s.%s",\
            argv[3],backFolder,argv[5],argv[6],argv[4]);
        }else{
            sprintf(cmd,"cd \"%s/%s\"; java %s",argv[3],argv[5],argv[4]);
        }
    }else if(!strcmp(argv[1], ".kt")){
        /*
            argv[1] type(.kt)
            argv[2] get this open.c's path
            argv[3] get path      [end without /]
            argv[4] get filename  [without extension]
            argv[5] output folder [end with /]
        */

        //Compile
        cmd_compile = malloc(65536 * sizeof(char));
        sprintf(cmd_compile, "cd %s & mkdir -p \"%s\" & kotlinc %s.kt -include-runtime -d \"%s%s.jar\"",\
                argv[2], argv[5], argv[4], argv[5], argv[4]);
        timerStart();
        if(system(cmd_compile) == -1){
            fprintf(stderr,"C, C++ or C# compile error\n");
        }
        compile_time = timerEnd();

        //Run
        cmd = malloc(65536 * sizeof(char));
        sprintf(cmd, "cd \"%s/%s\" & java -jar \"%s.jar\"",\
                argv[3], argv[5], argv[4]);
    }else if(!strcmp(argv[1],".c") || !strcmp(argv[1],".cpp") || !strcmp(argv[1],".cs")){
        cmd = malloc(65536 * sizeof(char));
        /*
            argv[1] type(.c , .cpp or .cs)
            argv[2] get path      [end without /]
            argv[3] get filename  [without extension]
            argv[4] output folder [end with /]
        */
        //Phase1: Compile
        if(!strcmp(argv[1],".c") || !strcmp(argv[1],".cpp")){
            sprintf(cmd, "cd \"%s\"; mkdir -p \"%s\" ; %s \"%s%s\" -lm -O2 -o \"%s%s\"",\
                    argv[2],argv[4],(!strcmp(argv[1],".c"))? "gcc" : "g++",\
                    argv[3],argv[1],argv[4],argv[3]);
        }else{
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\"; mcs -out:\"%s%s.exe\" \"%s.cs\"",\
                    argv[2], argv[4], argv[4], argv[3], argv[3]);
        }

        timerStart();
        if(system(cmd) == -1){
            fprintf(stderr,"C, C++ or C# compile error\n");
        }
        compile_time = timerEnd();
        cmd_compile  = malloc(65536 * sizeof(cmd));
        strcpy(cmd_compile, cmd);

        //Phase2: Run
        if(!strcmp(argv[1], ".c") || !strcmp(argv[1], ".cpp")){
            sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argv[2],argv[4],argv[3]);
        }else{
            sprintf(cmd,"cd \"%s/%s\"; mono \"%s.exe\"",argv[2],argv[4],argv[3]);
        }
    }else if(!strcmp(argv[1], ".rs")){
        cmd = malloc(65536 * sizeof(char));
        /*
            argv[1] type(.rs)
            argv[2] get path      [end without /]
            argv[3] get filename  [without extension]
            argv[4] output folder [end with /]
        */
        //Phase1: Compile
        sprintf(cmd,"cd \"%s\"; rustc \"%s.rs\" --out-dir \"%s\"",\
                argv[2],argv[3],argv[4]);


        timerStart();
        if(system(cmd)==-1){
            fprintf(stderr, "Compiled error\n");
        }
        compile_time = timerEnd();
        cmd_compile  = malloc(65536 * sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Run
        sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argv[2],argv[4],argv[3]);
    }else{
        //argv[1] command
        cmd = argv[1];
    }

    timerStart();
    if(system(cmd) == -1){
        fprintf(stderr, "Terminal error\n");
    }
    time = timerEnd();

    if(compile_time > 0){
        printf("\n--------------------------------\n");
        printf("%-12s%s\n%-12s%s\n\n",\
               "Compile:", cmd_compile, "Run:", cmd);
        printf("%-12s%.6lf s\n%-12s%.6lf s\n%-12s%.6lf s\n\n",\
               "Compiling:", ((double)compile_time)*(1e-6),\
               "Executing:", ((double)time)*(1e-6),\
               "Total:",     ((double)(compile_time+time))*(1e-6));
    }else if(assemble_time > 0){
        printf("\n--------------------------------\n");
        printf("%-12s%s\n%-12s%s\n%-12s%s\n\n",\
               "Assembling:", cmd_assemble, "Link:", cmd_link,"Run:", cmd);
        printf("%-12s%.6lf s\n%-12s%.6lf s\n%-12s%.6lf s\n%-12s%.6lf s\n\n",\
               "Assembling:", ((double)assemble_time)*(1e-6),\
               "Linking:",    ((double)link_time)*(1e-6),\
               "Execution:",  ((double)time)*(1e-6),\
               "Total:",      ((double)(assemble_time+link_time+time))*(1e-6));
    }else{
        printf("\n--------------------------------\n");
        printf("Run:  %s\n\n",cmd);
        printf("Time: %.6lf s\n\n",((double)time)*(1e-6));
    }
    /*
        printf("\n--------------------------------\n");
        for(i=0; i<argc; i++){
            printf("argc[%d] %s\n",i,argv[i]);
        }
        printf("command: %s\n",cmd);
    */
    pause();
}
