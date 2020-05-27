#include<conio.h>
int c_advance(char *str, char *str2, char **argv, float *compile_time){
    printf("Press \n\
        0: Compile only\n\
        1: Run old %s.exe\n\
        2: Specify output folder and then compile and run\n\
     else: Cancel\n", argv[2]);
    char choose;
    choose = getche();
    system("cls");
    if(choose == '0'){
        sprintf(str, "%s & chcp 65001 & md \"%s\" & cls & %s \"%s%s\" -o \"%s%s\"",\
                str, argv[6], !strcmp(argv[3],".c")? "gcc" : "g++", argv[2], argv[3], argv[6], argv[2]);
    }else if(choose == '1'){
        sprintf(str, "%s & cd \"%s\" & chcp 65001 & cls & \".\\%s.exe\"",\
                str, argv[6], argv[2]);
    }else if(choose == '2'){
        char* strtemp = malloc(sizeof(char) * strlen(str));
        strcpy(strtemp, str);

        printf("Please input the folder name (<256bits) you want to output file in. For example:\n");
        printf("out\\ , output\\c\\ , ..\\out\\ , .\\ , ..\\\n");

        char folder[256];
        scanf("%s", &folder);
        sprintf(str, "%s & chcp 65001 & md %s & %s \"%s%s\" -o %s\\%s",\
                str, folder, !strcmp(argv[3],".c")? "gcc" : "g++", argv[2], argv[3], folder, argv[2]);
        *compile_time = exec(str);
        strcpy(str2, str);
        sprintf(str, "%s & cd \"%s\" & chcp 65001 & cls & \"%s.exe\"",\
                strtemp, folder, argv[2]);
    }else{
        return 1;
    }
    return 0;
}

int go_advance(char *str, char **argv){
    printf("Press \n\
        0: Run\n\
        1: Build\n\
     else: Cancel\n");
    char choose;
    choose = getche();
    system("cls");
    if(choose == '0'){
        sprintf(str, "%s & go run \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose == '1'){
        printf("Building...\n");
        sprintf(str, "%s & go build \"%s%s\"",str,argv[2],argv[3]);
    }else{
        return 1;
    }
    return 0;
}

int py_advance(char *str,char **argv){
    printf("Press \n\
        0: Run\n\
        1: Build (by pyinstaller)\n\
     else: Cancel\n");

    char choose;
    choose = getche();
    system("cls");
    if(choose == '0'){
        sprintf(str,"%s & python \"%s%s\"",str,argv[2],argv[3]);
    }else if(choose == '1'){
        printf("Building...\n");
        sprintf(str,"%s & pyinstaller -F \"%s%s\"",str,argv[2],argv[3]);
    }else{
        return 1;
    }
    return 0;
}
