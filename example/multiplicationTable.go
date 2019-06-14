package main
import "fmt"
func main(){
    fmt.Print("hello GO! 哈囉 GO\n")
    for i:=2; i<10; i++{
        for j:=2; j<10; j++{
            fmt.Printf("%dx%d=%2d\t",j,i,i*j)
        }
        fmt.Print("\n")
    }
}
