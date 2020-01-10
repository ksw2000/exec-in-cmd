#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

char* execAndGet(const char* cmd){
    FILE* pipe=popen(cmd,"r");
    char* result=malloc(256*sizeof(char));
    strcpy(result,"0"); //preset

    if(!pipe){
        fprintf(stderr, "Exec-in-cmd Error: execAndGet() openLinux.c\n");
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
    struct  timeval  start, end;
    unsigned long compile_time=0, time=0;

    //Read file
    FILE* f=fopen(configFilepath,"r");
    if(f==NULL){
        fprintf(stderr, "Something wrong.");
        exit(1);
    }
    char argvf[6][1024];
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
        */
        //Phase1: Compile
        sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" -classpath \"%s\" \"%s.java\"",argvf[3],argvf[5],argvf[5],argvf[5],argvf[4]);
        gettimeofday(&start,NULL);
        system(cmd);
        gettimeofday(&end,NULL);
        compile_time=1000000*(end.tv_sec-start.tv_sec)+ end.tv_usec-start.tv_usec;

        cmd_compile=malloc(1024*sizeof(cmd));
        strcpy(cmd_compile,cmd);

        //Phase2: Get package name
        sprintf(cmd,"%s/readPackageDarwin -p %s/%s.java",argvf[2],argvf[3],argvf[4]);
        packageName=execAndGet(cmd);

        //Phase3: Run
        sprintf(cmd,"cd \"%s/%s\"; java ",argvf[3],argvf[5]);
        if(strcmp(packageName,"0")){ //If execAndGetCanRun and package!="0"
            strcat(cmd,packageName);
            strcat(cmd,".");
        }
        sprintf(cmd,"%s%s",cmd,argvf[4]);
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
/*
        if(!strcmp(argv[0],".c") || !strcmp(argv[0],".cpp") || !strcmp(argv[0],".cs")){
            printf("for c language");
        }else if(!strcmp(argv[0],".java")){
            printf("for java");
        }else{
            printf("%s",argv[0]);
            system("reset");
            system(argv[0]);
        }
*/
    pause();
    exit(0);
}
