public class fibonacci{
    public static void main(String[] args){
        System.out.println("Hello java! 哈囉 java！");
        System.out.println("fibonacci sequence：");
        int i=1,j=0,tmp;
        for(int k=0; k<20; k++){
            System.out.println("f("+k+")="+j);
            tmp=j;
            j=i+j;
            i=tmp;
        }
    }
}
