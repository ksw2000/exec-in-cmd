#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"function.h"
#include"advance.h"

int main(int argc, char *argv[]){
    //strcmp is a function compare two strings. If they are same, return 0
    //argv[1] get path (end without \)
    //argv[2] get filename (not including extension)
    //argv[3] get filename extension (start with .)
    //argv[4] get this open.c's path (end without \)
    //argv[5] 1: if use advance mode , 0: else
    //argv[6] output folder (end with \)

    int exit=0,packageFlag=0;
    float compile_time=0.0,exec_time=0.0,total_time=0.0;
    clock_t start_compile_time,end_compile_time;
    int advance=(strcmp(argv[5],"1")==0)? 1:0;
    char *str,*str2;
    size_t length = strlen(argv[1]) + strlen(argv[2]) + strlen(argv[3]) + strlen(argv[4]) + 512;
    str=calloc(length, sizeof(char));
    str2=calloc(length, sizeof(char));

    sprintf(str,"cd \"%s\"",argv[1]);
    if(strcmp(argv[3],".java")==0){
        if(advance==1){
            exit=java_advance(str,str2,argv,&compile_time,&packageFlag);
        }else{
            //Compile
            sprintf(str,"%s & md \"%s\" & cls & javac -encoding UTF-8 -d %s -classpath %s %s%s",str,argv[6],argv[6],argv[6],argv[2],argv[3]);
            compile_time=exec(str);
            strcpy(str2,str);
            clear(str);

            //Run
            char getPackage[256]="";
            char packageName[256]="";
            sprintf(getPackage,"%s\\readPackage.exe -p \"%s\\%s%s\" ",argv[4],argv[1],argv[2],argv[3]);
            sprintf(str,"cd \"%s\\%s\" & java ",argv[1],argv[6]);

            //If use package
            if(execAndGet(getPackage,packageName)==1){
                if(strcmp(packageName,"0")!=0){
                    sprintf(str,"%s%s.",str,packageName);
                    packageFlag=1;
                }
            }

            sprintf(str,"%s%s",str,argv[2]);
        }

    }else if(strcmp(argv[3],".c")==0 || strcmp(argv[3],".cpp")==0){
        if(advance==1){
            exit=c_advance(str,str2,argv,&compile_time);
        }else{
            sprintf(str,"%s & chcp 65001 & md \"%s\" & cls &",str,argv[6]);
            if(strcmp(argv[3],".c")==0){
                sprintf(str,"%s gcc",str);
            }else{
                sprintf(str,"%s g++",str);
            }

            sprintf(str,"%s \"%s%s\" -O2 -o \"%s%s\"",str,argv[2],argv[3],argv[6],argv[2]);
            compile_time=exec(str);
            strcpy(str2,str);
            clear(str);

            sprintf(str,"cd \"%s\\%s\" & \"%s.exe\"",argv[1],argv[6],argv[2]);
        }
    }else if(strcmp(argv[3],".cs")==0){
        sprintf(str,"%s & md \"%s\" & cls & mcs -out:\"%s%s.exe\" \"%s.cs\"",\
                str,argv[6],argv[6],argv[2],argv[2]);
        compile_time=exec(str);
        strcpy(str2,str);
        clear(str);

        sprintf(str,"cd \"%s\\%s\" & \"%s.exe\"",argv[1],argv[6],argv[2]);
    }else if(strcmp(argv[3],".py")==0){
        if(advance==1){
            exit=py_advance(str,argv);
        }else{
            sprintf(str,"%s & python \"%s%s\"",str,argv[2],argv[3]);
        }
    }else if(strcmp(argv[3],".js")==0){
        sprintf(str,"%s & node \"%s%s\"",str,argv[2],argv[3]);
    }else if(strcmp(argv[3],".go")==0){
        if(advance==1){
            exit=go_advance(str,argv);
        }else{
            sprintf(str,"%s & go run \"%s%s\"",str,argv[2],argv[3]);
        }
    }else if(strcmp(argv[3],".R")==0){
        sprintf(str,"%s & chcp 65001 & cls & Rscript \"%s%s\"",str,argv[2],argv[3]);
    }else if(strcmp(argv[3],".rb")==0){
        sprintf(str,"%s & chcp 65001 & cls & ruby \"%s%s\"",str,argv[2],argv[3]);
    }else{
        exit=not_support(str);
        return 0;
    }

    if(argv[0]==0){
        printf("You have not chosen a file.");
    }else{
        exec_time=exec(str);

        if(compile_time>0){
            total_time=compile_time+exec_time;
            printf("\n--------------------------------\n");
            printf("Compiling command:\t%s\nRunning command:\t%s\n",str2,str);
            printf("\n--------------------------------\n");
            printf("Compilation Time:\t%.4f s\nExecution Time:\t\t%.4f s\nTotal Time:\t\t%.4f s\n\n",compile_time,exec_time,total_time);
        }else{
            printf("\n--------------------------------\n");
            printf("Command:\n%s\n\n",str);
            printf("Total Time: %.4f s\n\n",exec_time);
        }
    }

    if(exit==0){
        system("pause");
    }

	return 0;
}
