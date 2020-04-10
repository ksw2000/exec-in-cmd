float exec(char str[]){
    clock_t start,end;
    start=clock();
    system(str);
    end=clock();
    float time=(float)(end-start)/CLOCKS_PER_SEC;
    return time;
}

void error_try_again(){
    //Print highlight and yellow string
    //background-color  40: black
    //font color        31: red  32: green
    //other style       1m: highlight
    printf("\033[40;31;1merror! Try again!\033[0m\n");
    system("pause");
    system("cls");
}
