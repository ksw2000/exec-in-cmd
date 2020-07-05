package main
import "fmt"
func main(){
    fmt.Println("Multiplication Table")
    for i:=2; i<10; i++{
        for j:=2; j<10; j++{
            fmt.Printf("%d×%d = %2d  ", j, i, i*j)
        }
        fmt.Println()
    }
}
