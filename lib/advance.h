int c_advance(char *str, char **argv, float *compile_time){
    printf("Input \n\t0: Compile only\n\t1: Specify output folder\n\t2: Open cmd\n");
    int choose;
    scanf("%d",&choose);
    system("cls");
    if(choose==0){
        sprintf(str,"%s & chcp 65001 & md out & cls &",str);
        if(strcmp(argv[3],".c")==0){
            sprintf(str,"%s gcc",str);
        }else{
            sprintf(str,"%s g++",str);
        }
        sprintf(str,"%s \"%s%s\" -o \"out\\%s\"",str,argv[2],argv[3],argv[2]);
    }else if(choose==1){
        //system("cls");
        printf("Please input the folder name (<128) you want to output file in. For example: out\n");
        printf("If you want to output the same folder the sorce file in, please input \\\n");

        char folder[128];
        scanf("%s",&folder);
        int flagFolderName=(strcmp(folder,"\\")==0)? 0 : 1;

        sprintf(str,"%s & chcp 65001",str);

        if(flagFolderName!=0){
            sprintf(str,"%s & md %s",str,folder);
        }

        if(strcmp(argv[3],".c")==0){
            sprintf(str,"%s & gcc \"%s%s\" -o ",str,argv[2],argv[3]);
        }else{
            sprintf(str,"%s & g++ \"%s%s\" -o ",str,argv[2],argv[3]);
        }

        if(flagFolderName!=0){
            sprintf(str,"%s\"%s\\",str,folder);
        }

        sprintf(str,"%s%s\"",str,argv[2]);
        *compile_time=exec(str);

        //printf("Done! Press 1 to run or another key to quit\n");
        sprintf(str,"cd \"%s\\%s\" & chcp 65001 & cls & \"%s.exe\"",argv[1],folder,argv[2]);

        //printf("Do you want to output c and c++ in this folder always? 1/0");
    }else if(choose==2){
        sprintf(str,"%s & start",str);
        return 1;
    }else{
        error_try_again();
        return c_advance(str,argv,compile_time);
    }
    return 0;
}

int go_advance(char *str,char **argv){
    printf("Input \n\t0: Run\n\t1: Build\n\t2: Open cmd\n");
    int choose;
    scanf("%d",&choose);
    system("cls");
    if(choose==0){
        sprintf(str,"%s & go run \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose==1){
        printf("Building...\n");
        sprintf(str,"%s & go build \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose==2){
        sprintf(str,"%s & start",str);
        return 1;
    }else{
        error_try_again();
        return go_advance(str,argv);
    }
    return 0;
}
