#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char* execAndGet(const char* cmd){
    FILE* pipe=popen(cmd,"r");
    char* packageName=malloc(256*sizeof(char));

    if(!pipe){
        fprintf(stderr,"Exec-in-cmd Error: execAndGet() openLinux.c\n");
        exit(EXIT_FAILURE);
    }

    while(!feof(pipe)){
        fgets(packageName,256,pipe);
    }
    pclose(pipe);
    return packageName;
}

void pause(){
    printf("Press any key to continue...");
    char c;
    c=getc(stdin);
}

int main(int argc, char** argv){
    int i;
    char *cmd, *packageName;
    if(!strcmp(argv[1],"java")){
        cmd=malloc(1024*sizeof(char));
        /*
            argv[1] type(java)
            argv[2] get this open.c's path
            argv[3] get path      [end without /]
            argv[4] get filename  [without extension]
            argv[5] output folder [end with /]
        */
        //Phase1: Compile
        sprintf(cmd,"cd \"%s\"; mkdir -p \"%s\" ; javac -encoding UTF-8 -d \"%s\" -classpath \"%s\" \"%s.java\"",argv[3],argv[5],argv[5],argv[5],argv[4]);
        system(cmd);

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

        system(cmd);
    }else{
        //argv[1] command
        system(argv[1]);
    }

    printf("\n--------------------------------\n");
    for(i=0; i<argc; i++){
        printf("argc[%d] %s\n",i,argv[i]);
    }
    printf("command: %s\n",(!strcmp(argv[1],"java"))? cmd : argv[1]);
    pause();
}
