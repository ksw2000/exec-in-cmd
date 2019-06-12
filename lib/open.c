#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
int execAndGet(char* cmd, char* result){
    char buffer[512];
    FILE* pipe = _popen(cmd, "r");
    if (!pipe){
        return 0;   //Return 0 if fail.
    }
    while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe)){
            strcat(result,buffer);
        }
    }
    _pclose(pipe);
    return 1;   //Return 0 if success.
}

int clean(char *p){
    *p='\0';
}

float exec(char str[]){
    clock_t start,end;
    start=clock();
    system(str);
    end=clock();
    float time=(float)(end-start)/CLOCKS_PER_SEC;
    return time;
}

int main(int argc, char *argv[]){
	//strcmp is a function compare two strings. If they are same, return 0
	//argv[1] return path (not including \)
    //argv[2] return filename (not including extension)
    //argv[3] return filename extension (including point)
    //argv[4] return this open.c's path (not including \)
	char str[1024]="",str2[1024]="";
    int error=0,exit=0,packageFlag=0;
    float compile_time=0.0,exec_time=0.0,total_time=0.0;
    clock_t start_compile_time,end_compile_time;
    strcat(str,"cd \"");
    strcat(str,argv[1]);
    strcat(str,"\"");
	if(strcmp(argv[3],".java")==0){
        //Compile
		strcat(str," & md out & cls & javac -encoding UTF-8 -d out -classpath out ");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
        compile_time=exec(str);
        strcpy(str2,str);
        clean(str);

        //Run
        char getPackage[256]="";
        char packageName[256]="";

        strcat(getPackage,argv[4]);
        strcat(getPackage,"\\readPackage.exe -p \"");
        strcat(getPackage,argv[1]);
        strcat(getPackage,"\\");
        strcat(getPackage,argv[2]);
        strcat(getPackage,argv[3]);
        strcat(getPackage,"\"");

        strcat(str,"cd \"");
        strcat(str,argv[1]);
        strcat(str,"\\out\" & java ");
        if(execAndGet(getPackage,packageName)==1){
            if(strcmp(packageName,"0")!=0){
        		strcat(str,packageName);
        		strcat(str,".");
                packageFlag=1;
            }
    		strcat(str,argv[2]);
        }else{
            printf("file not found");
        }

    }else if(strcmp(argv[3],".c")==0 || strcmp(argv[3],".cpp")==0){
        strcat(str," & chcp 65001 & md out & cls & ");
		if(strcmp(argv[3],".c")==0){
			strcat(str,"gcc");
		}else{
			strcat(str,"g++");
		}
        strcat(str," \"");
        strcat(str,argv[2]);
        strcat(str,argv[3]);
		strcat(str,"\" -o \"out\\");
		strcat(str,argv[2]);
		strcat(str,"\"");
        compile_time=exec(str);
        strcpy(str2,str);
        clean(str);

        strcat(str,"cd \"");
        strcat(str,argv[1]);
        strcat(str,"\\out\" & \"");
		strcat(str,argv[2]);
		strcat(str,".exe\"");
	}else if(strcmp(argv[3],".py")==0){
		strcat(str," & python \"");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
        strcat(str,"\"");
	}else if(strcmp(argv[3],".go")==0){
		strcat(str," & go run \"");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
        strcat(str,"\"");
	}else if(strcmp(argv[3],".R")==0){
		strcat(str," & chcp 65001 & cls & Rscript \"");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
		strcat(str,"\"");
	}else if(strcmp(argv[3],".rb")==0){
		strcat(str," & chcp 65001 & cls & ruby \"");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
		strcat(str,"\"");
	}else if(strcmp(argv[3],".html")==0 || strcmp(argv[3],".htm")==0 || strcmp(argv[3],".pdf")==0 || strcmp(argv[3],".lnk")==0){
        strcat(str," & start \"\" \"");
        strcat(str,argv[1]);
        strcat(str,"\\");
        strcat(str,argv[2]);
        strcat(str,argv[3]);
        strcat(str,"\"");
        exit=1;     //We don't need command line if we open the types of files
    }else{
        error=(argv[0]==0)? 2:3;
    }

    if(error==1){
        printf("The filepath extension is not supported.\n");
    }else if(error==2){
        printf("You have not chosen a file.");
    }else{
        exec_time=exec(str);

        if(compile_time>0){
            total_time=compile_time+exec_time;
            printf("\n--------------------------------\n");
            printf("Compiling command:\t%s\nRunning command:\t%s\n",str2,str);
            printf("\n--------------------------------\n");
            printf("Compilation Time:\t%.4f s\nExecution Time:\t\t%.4f s\nTotal Time:\t\t%.4f s",compile_time,exec_time,total_time);
            if(packageFlag==1){
                printf("\nUsing package\n\n");
            }else{
                printf("\n\n");
            }
        }else{
            printf("\n\nCommand:\n%s\n\n",str);
            printf("Total Time: %.4f s\n\n",exec_time);
        }
    }

    if(exit==0){
        system("pause");
    }

	return 0;
}
