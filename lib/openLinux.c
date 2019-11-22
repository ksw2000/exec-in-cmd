#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

char* execAndGet(const char* cmd){
    FILE* pipe=popen(cmd,"r");
    char* result=malloc(256*sizeof(char));
    strcpy(result,"0"); //preset

    if(!pipe){
        fprintf(stderr,"Exec-in-cmd Error: execAndGet() openLinux.c\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(pipe)){
        fgets(result,sizeof(result),pipe);
    }
    pclose(pipe);
    return result;
}

void pause(){
    printf("Press any key to continue...");
    char c;
    c=getc(stdin);
}

int main(int argc, char** argv){

    //sprintf(cmd,"sudo chmod -R 777 %s",argv[2]);
    //system(cmd);

    //Timecounter
    float compile_time, time;
    clock_t start,end;

    int i;
    char *cmd, *cmd_compile, *packageName;
    if(!strcmp(argv[1],".java")){
        cmd=malloc(1024*sizeof(char));
        /*
            argv[1] type(.java)
            argv[2] get this open.c's path
            argv[3] get path      [end without /]
            argv[4] get filename  [without extension]
            argv[5] output folder [end with /]
        */

        //Phase1: Compile
        sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" -classpath \"%s\" \"%s.java\"",argv[3],argv[5],argv[5],argv[5],argv[4]);
        start=clock();
        system(cmd);
        end=clock();
        compile_time=(float)(end-start)/CLOCKS_PER_SEC;
        cmd_compile = malloc(1024*sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Get package name
        sprintf(cmd,"%s/readPackage -p %s/%s.java",argv[2],argv[3],argv[4]);
        packageName=execAndGet(cmd);

        //Phase3: Run
        sprintf(cmd,"cd \"%s/%s\"; java ",argv[3],argv[5]);
        if(strcmp(packageName,"0")){ //If execAndGetCanRun and package!="0"
            strcat(cmd,packageName);
            strcat(cmd,".");
        }
        sprintf(cmd,"%s%s",cmd,argv[4]);
    }else if(!strcmp(argv[1],".c") || !strcmp(argv[1],".cpp")){
        cmd=malloc(1024*sizeof(char));
        char compiler[4];
        /*
            argv[1] type(.c or .cpp)
            argv[2] get this open.c's path
            argv[3] get path      [end without /]
            argv[4] get filename  [without extension]
            argv[5] output folder [end with /]
        */
        //Phase1: Compile
        strcpy(compiler,(!strcmp(argv[1],".c"))? "gcc" : "g++");
        sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; %s \"%s%s\" -lm -O2 -o \"%s%s\"",\
                argv[3],argv[5],(!strcmp(argv[1],".c"))? "gcc" : "g++",\
                argv[4],argv[1],argv[5],argv[4]);
        start=clock();
        system(cmd);
        end=clock();
        compile_time=(float)(end-start)/CLOCKS_PER_SEC;
        cmd_compile = malloc(1024*sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Run
        sprintf(cmd,"cd \"%s/%s\"; \"./%s\"",argv[3],argv[5],argv[4]);
    }else{
        //argv[1] command
        cmd=argv[1];
    }

    start=clock();
    system(cmd);
    end=clock();
    time=(float)(end-start)/CLOCKS_PER_SEC;

    if(compile_time>0){
        printf("\n--------------------------------\n");
        printf("Compiling command:\t%s\nRunning command:\t%s\n",cmd_compile,cmd);
        printf("\n--------------------------------\n");
        printf("Compilation Time:\t%.4f s\nExecution Time:\t\t%.4f s\nTotal Time:\t\t%.4f s",compile_time,time,compile_time+time);
    }else{
        printf("\n--------------------------------\n");
        printf("Command:\n%s\n\n",cmd);
        printf("Total Time: %.4f s\n\n",time);
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
