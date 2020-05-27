float exec(char str[]){
    clock_t start,end;
    start=clock();
    system(str);
    end=clock();
    float time=(float)(end-start)/CLOCKS_PER_SEC;
    return time;
}
