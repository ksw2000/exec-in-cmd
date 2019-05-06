#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
	char str[1024]="";
    int error=0,exit=0;
    float compile_time=0.0,exec_time=0.0,total_time=0.0;
    clock_t start_compile_time,end_compile_time;
    strcat(str,"cd \"");
    strcat(str,argv[1]);
    strcat(str,"\"");
	if(strcmp(argv[3],".java")==0){
		strcat(str," & md out & cls & javac -encoding UTF-8 -d out ");
		strcat(str,argv[2]);
		strcat(str,argv[3]);
        compile_time=exec(str);
        clean(str);
        strcat(str,"cd \"");
        strcat(str,argv[1]);
		strcat(str,"\\out\" & java ");
		strcat(str,argv[2]);
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
	}else if(strcmp(argv[3],".html")==0 || strcmp(argv[3],".htm")==0 || strcmp(argv[3],".pdf")==0 || strcmp(argv[3],".lnk")==0){
        strcat(str," & start \"\" \"");
        strcat(str,argv[1]);
        strcat(str,"\\");
        strcat(str,argv[2]);
        strcat(str,argv[3]);
        strcat(str,"\"");
        exit=1;
    }else{
        error=(argv[0]==0)? 2:3;
    }

    if(error==1){
        printf("The filepath extension is not supported.\n");
    }else if(error==2){
        printf("You didn't choose a file.");
    }else{
        exec_time=exec(str);

        if(compile_time>0){
            total_time=compile_time+exec_time;
            printf("\n--------------------------------\n");
            printf("Compilation Time:\t%.4f s\nExecution Time:\t\t%.4f s\nTotal Time:\t\t%.4f s\n\n",compile_time,exec_time,total_time);
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
