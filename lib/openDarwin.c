#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

void pause(){
    printf("Press any key to continue...");
    char c;
    c = getc(stdin);
}

int main(int argc, char** argv){
    int i;
    //Prepare for reading file
    int stringLen = strlen(argv[0])+32;
    char* configFilepath = calloc(stringLen, sizeof(char));
    strcpy(configFilepath, argv[0]);
    for(i = stringLen-1; i >= 0; i--){
        if(configFilepath[i] == '/'){
            configFilepath[i] = '\0';
            break;
        }
    }
    strcat(configFilepath, "/configTemp.tmp");

    //Timecounter and some variables
    char *cmd, *cmd_compile, *packageName;
    struct timeval start, end;
    unsigned long compile_time = 0, time = 0;

    //Read file
    FILE* f = fopen(configFilepath,"r");
    if(!f){
        fprintf(stderr, "Something wrong.");
        exit(1);
    }
    char argvf[7][65536];
    for(i = 1; fgets(argvf[i], 65536, f); i++){
        argvf[i][strlen(argvf[i])-1]='\0';
    }
    system("clear && printf '\\e[3J'");

    if(!strcmp(argvf[1], ".java")){
        cmd = malloc(65536*sizeof(char));
        /*
            argvf[1] type(.java)
            argvf[2] get this open.c's path
            argvf[3] get path      [end without /]
            argvf[4] get filename  [without extension]
            argvf[5] output folder [end with /]
            argvf[6] package name
        */

        //Phase1: Compile
        char* backFolder = malloc(128*sizeof(char));
        if(strcmp(argvf[6], "0")){
            strcpy(backFolder, "../");
            int i;
            for(i = 0; i < strlen(argvf[6]); i++){
                if(argvf[6][i] == '.'){
                    strcat(backFolder, "../");
                }
            }
            sprintf(cmd, "cd \"%s\"; mkdir -p \"%s%s\" ; javac -encoding UTF-8 -d \"%s%s\" -classpath \"%s%s\" \"%s.java\"",
                    argvf[3], backFolder, argvf[5], backFolder, argvf[5], backFolder, argvf[5], argvf[4]);
        }else{
            sprintf(cmd, "cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" -classpath \"%s\" \"%s.java\"",
                    argvf[3], argvf[5], argvf[5], argvf[5], argvf[4]);
        }

        gettimeofday(&start, NULL);
        system(cmd);
        gettimeofday(&end, NULL);
        compile_time = 1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
        cmd_compile  = malloc(65536*sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Run
        if(strcmp(argvf[6], "0")){
            sprintf(cmd, "cd \"%s\"; cd \"%s\"; cd \"%s\"; java %s.%s",\
                    argvf[3], backFolder, argvf[5], argvf[6], argvf[4]);
        }else{
            sprintf(cmd, "cd \"%s/%s\"; java %s",\
                    argvf[3], argvf[5], argvf[4]);
        }
    }else if(!strcmp(argvf[1],".c") || !strcmp(argvf[1],".cpp") || !strcmp(argvf[1],".cs")){
        cmd = malloc(65536*sizeof(char));
        /*
            argvf[1] type(.c , .cpp or .cs)
            argvf[2] get this open.c's path
            argvf[3] get path      [end without /]
            argvf[4] get filename  [without extension]
            argvf[5] output folder [end with /]
        */
        //Phase1: Compile
        if(!strcmp(argvf[1],".c") || !strcmp(argvf[1],".cpp")){
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; %s \"%s%s\" -lm -O2 -o \"%s%s\"",\
                    argvf[3],argvf[5],(!strcmp(argvf[1],".c"))? "gcc" : "g++",\
                    argvf[4],argvf[1],argvf[5],argvf[4]);
        }else{
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\"; mcs -out:\"%s%s.exe\" \"%s.cs\"",\
                    argvf[3], argvf[5], argvf[5], argvf[4], argvf[4]);
        }

        gettimeofday(&start, NULL);
        system(cmd);
        gettimeofday(&end, NULL);
        compile_time = 1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
        cmd_compile  = malloc(65536*sizeof(cmd));
        strcpy(cmd_compile, cmd);

        //Phase2: Run
        if(!strcmp(argvf[1],".c") || !strcmp(argvf[1],".cpp")){
            sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argvf[3],argvf[5],argvf[4]);
        }else{
            sprintf(cmd,"cd \"%s/%s\"; mono \"%s.exe\"",argvf[3],argvf[5],argvf[4]);
        }
    }else if(!strcmp(argvf[1], ".rs")){
      cmd = malloc(65536*sizeof(char));
      /*
          argvf[1] type(.rs)
          argvf[2] get this open.c's path
          argvf[3] get path      [end without /]
          argvf[4] get filename  [without extension]
          argvf[5] output folder [end with /]
      */
      //Phase1: Compile
      sprintf(cmd,"cd \"%s\"; rustc \"%s.rs\" --out-dir \"%s\"",\
              argvf[3],argvf[4],argvf[5]);
      gettimeofday(&start, NULL);
      system(cmd);
      gettimeofday(&end, NULL);
      compile_time = 1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;
      cmd_compile  = malloc(65525 * sizeof(cmd));
      strcpy(cmd_compile,cmd);

      //Phase2: Run
      sprintf(cmd,"cd \"%s/%s\"; \"./%s\"", argvf[3], argvf[5], argvf[4]);
    }else{
        //argvf[1] command
        cmd = argvf[1];
    }

    gettimeofday(&start, NULL);
    system(cmd);
    gettimeofday(&end, NULL);
    time = 1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;

    if(compile_time > 0){
        printf("\n--------------------------------\n");
        printf("%-12s%s\n%-12s%s\n\n",\
               "Compile:", cmd_compile, "Run:", cmd);
        printf("\n--------------------------------\n");
        printf("%-12s%.6lf s\n%-12s%.6lf s\n%-12s%.6lf s\n\n",\
               "Compiling:", ((double)compile_time)*(10e-7),\
               "Executing:", ((double)time)*(10e-7),\
               "Total:",     ((double)(compile_time+time))*(10e-7));
    }else{
       printf("\n--------------------------------\n");
       printf("Run:  %s\n\n", cmd);
       printf("Time: %.6lf s\n\n", ((double)time)*(10e-7));
    }

    pause();
    exit(0);
}
