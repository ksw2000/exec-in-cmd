public class fibonacci{
    public static void main(String[] args){
        System.out.println("Hello java! 哈囉 java！");
        System.out.println("fibonacci sequence:");
        int i=1,j=0,tmp;
        for(int k=0; k<30; k++){
            System.out.printf("f(%d)%s%d\n", k, (k<10)?"  = ":" = ", j);
            tmp=j;
            j=i+j;
            i=tmp;
        }
    }
}
