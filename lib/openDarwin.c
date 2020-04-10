#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

void pause(){
    printf("Press any key to continue...");
    char c;
    c=getc(stdin);
}

int main(int argc, char** argv){
    int i;
    //Prepare for reading file
    char* configFilepath;
    int stringLen = strlen(argv[0])+32;
    configFilepath = calloc(stringLen ,sizeof(char));
    strcpy(configFilepath, argv[0]);
    for(i=stringLen-1; i>=0; i--){
        if(configFilepath[i]=='/'){
            configFilepath[i]='\0';
            break;
        }
    }
    strcat(configFilepath,"/configTemp.tmp");

    //Timecounter and some variables
    char *cmd, *cmd_compile, *packageName;
    struct timeval start, end;
    unsigned long compile_time=0, time=0;

    //Read file
    FILE* f=fopen(configFilepath,"r");
    if(f==NULL){
        fprintf(stderr, "Something wrong.");
        exit(1);
    }
    char argvf[7][1024];
    for(i=1; fgets(argvf[i],1024,f); i++){
        argvf[i][strlen(argvf[i])-1]='\0';
    }
    system("clear && printf '\\e[3J'");

    if(!strcmp(argvf[1],".java")){
        cmd=malloc(1024*sizeof(char));
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
            strcpy(backFolder,"../");
            int i;
            for(i=0; i<strlen(argvf[6]); i++){
                if(argvf[6][i] == '.'){
                    strcat(backFolder, "../");
                }
            }
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s%s\" ; javac -encoding UTF-8 -d \"%s%s\" -classpath \"%s%s\" \"%s.java\"",argvf[3],backFolder,argvf[5],backFolder,argvf[5],backFolder,argvf[5],argvf[4]);
        }else{
            sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" -classpath \"%s\" \"%s.java\"",argvf[3],argvf[5],argvf[5],argvf[5],argvf[4]);
        }

        gettimeofday(&start,NULL);
        if(system(cmd)==-1){
            fprintf(stderr,"Java compile error\n");
        }
        gettimeofday(&end,NULL);
        compile_time=1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;

        strcpy(cmd_compile,cmd);

        //Phase2: Run
        if(strcmp(argvf[6], "0")){
            sprintf(cmd,"cd \"%s\"; cd \"%s\"; cd \"%s\"; java %s.%s",argvf[3],backFolder,argvf[5],argvf[6],argvf[4]);
        }else{
            sprintf(cmd,"cd \"%s/%s\"; java %s",argvf[3],argvf[5],argvf[4]);
        }
    }else if(!strcmp(argvf[1],".c") || !strcmp(argvf[1],".cpp") || !strcmp(argvf[1],".cs")){
        cmd=malloc(1024*sizeof(char));
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

        gettimeofday(&start,NULL);
        system(cmd);
        gettimeofday(&end,NULL);
        compile_time=1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec;
        cmd_compile = malloc(1024*sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Run
        if(!strcmp(argvf[1],".c") || !strcmp(argvf[1],".cpp")){
            sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argvf[3],argvf[5],argvf[4]);
        }else{
            sprintf(cmd,"cd \"%s/%s\"; mono \"%s.exe\"",argvf[3],argvf[5],argvf[4]);
        }

    }else{
        //argvf[1] command
        cmd=argvf[1];
    }

    gettimeofday(&start,NULL);
    system(cmd);
    gettimeofday(&end,NULL);
    time=1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;

    if(compile_time>0){
        printf("\n--------------------------------\n");
        printf("Compiling command:\t%s\nRunning command:\t%s\n",cmd_compile,cmd);
        printf("\n--------------------------------\n");
        printf("Compilation Time:\t%.6lf s\nExecution Time:\t\t%.6lf s\nTotal Time:\t\t%.6lf s\n\n",\
        ((double)compile_time)*(10e-7),((double)time)*(10e-7),((double)(compile_time+time))*(10e-7));
    }else{
        printf("\n--------------------------------\n");
        printf("Command:\n%s\n\n",cmd);
        printf("Total Time: %.6lf s\n\n",((double)time)*(10e-7));
    }

    pause();
    exit(0);
}
