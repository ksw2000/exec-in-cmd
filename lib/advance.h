int c_advance(char *str, char *str2, char **argv, float *compile_time){
    printf("Input \n\t0: Compile only\n\t1: Run old %s.exe\n\t2: Specify output folder and then compile and run\n",argv[2]);
    int choose;
    scanf("%d",&choose);
    system("cls");
    if(choose==0){
        sprintf(str,"%s & chcp 65001 & md \"%s\" & cls &",str,argv[6]);
        if(strcmp(argv[3],".c")==0){
            sprintf(str,"%s gcc",str);
        }else{
            sprintf(str,"%s g++",str);
        }
        sprintf(str,"%s \"%s%s\" -o \"%s%s\"",str,argv[2],argv[3],argv[6],argv[2]);
    }else if(choose==1){
        sprintf(str,"cd \"%s\\%s\" & chcp 65001 & cls & \"%s.exe\"",argv[1],argv[6],argv[2]);
    }else if(choose==2){
        printf("Please input the folder name (<256) you want to output file in. For example:\n");
        printf("out\\ , output\\c\\ , ..\\out\\ , .\\ , ..\\\n");

        char folder[256];
        scanf("%s",&folder);

        sprintf(str,"%s & chcp 65001 & md %s & g",str,folder);
        if(strcmp(argv[3],".c")==0){
            sprintf(str,"%scc",str);
        }else{
            sprintf(str,"%s++",str);
        }
        sprintf(str,"%s \"%s%s\" -o %s\\%s",str,argv[2],argv[3],folder,argv[2]);
        *compile_time=exec(str);
        strcpy(str2,str);
        sprintf(str,"cd \"%s\\%s\" & chcp 65001 & cls & \"%s.exe\"",argv[1],folder,argv[2]);
    }else{
        error_try_again();
        return c_advance(str,str2,argv,compile_time);
    }
    return 0;
}

int go_advance(char *str,char **argv){
    printf("Input \n\t0: Run\n\t1: Build\n");
    int choose;
    scanf("%d",&choose);
    system("cls");
    if(choose==0){
        sprintf(str,"%s & go run \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose==1){
        printf("Building...\n");
        sprintf(str,"%s & go build \"%s%s\"",str,argv[2],argv[3]);
    }else{
        error_try_again();
        return go_advance(str,argv);
    }
    return 0;
}

int py_advance(char *str,char **argv){
    printf("Input \n\t0: Run\n\t1: Build (by pyinstaller)\n");
    int choose;
    scanf("%d",&choose);
    system("cls");
    if(choose==0){
        sprintf(str,"%s & python \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose==1){
        printf("Building...\n");
        sprintf(str,"%s & pyinstaller -F \"%s%s\"",str,argv[2],argv[3]);
    }else{
        error_try_again();
        return py_advance(str,argv);
    }
    return 0;
}
