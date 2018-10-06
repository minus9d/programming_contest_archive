package main
import "fmt"

func main(){
	var n int 
	fmt.Scan(&n)
    if n == 1 {
        fmt.Print("Hello World")
    } else {
		var a, b int
		fmt.Scan(&a)
		fmt.Scan(&b)
        fmt.Print(a + b)
    }
}
