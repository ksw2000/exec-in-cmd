package main
import (
    "fmt"
    "io/ioutil"
    "flag"
    "regexp"
)
func main() {
    var filepath=flag.String("p","0","add file path")
    flag.Parse()

    b, err := ioutil.ReadFile(*filepath)
    if err != nil {
        fmt.Print(err)
    }
     
    re := regexp.MustCompile(`(?m)^\s{0,}package\b\s[a-zA-Z_$]+[a-zA-Z0-9._$]{0,};`)
    first := re.FindStringSubmatch(string(b))
    if len(first)!=0 {
        re2 := regexp.MustCompile(`[a-zA-Z_$]+[a-zA-Z0-9._$]{0,};`)
        second := re2.FindStringSubmatch(first[0]);
        re3 := regexp.MustCompile(`[a-zA-Z_$]+[a-zA-Z0-9._$]{0,}`)
        third := re3.FindStringSubmatch(second[0]);
        fmt.Printf("%s",third[0])
    }else{
        fmt.Print("0")
    }
}
