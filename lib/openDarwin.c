#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/time.h>

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
    int i;
    //readFile
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
    printf("\n\n--%s--\n\n",configFilepath);
    strcat(configFilepath,"/configTemp.tmp");
    printf("\n\n--%s--\n\n",configFilepath);

    FILE* f=fopen(configFilepath,"r");
    if(f==NULL){
        fprintf(stderr, "Something wrong.");
        exit(1);
    }else{
        char buffer[5][1024];
        for(i=0; fgets(buffer[i],1024,f); i++){
            buffer[i][strlen(buffer[i])-1]='\0';
        }

        if(!strcmp(buffer[0],".c") || !strcmp(buffer[0],".cpp") || !strcmp(buffer[0],".cs")){
            printf("for c language");
        }else if(!strcmp(buffer[0],".java")){
            printf("for java");
        }else{
            printf("%s",buffer[0]);
            system("reset");
            system(buffer[0]);
        }
    }
    pause();
    exit(0);
}
