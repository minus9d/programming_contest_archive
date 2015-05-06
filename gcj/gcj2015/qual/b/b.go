// reference
//   http://golang.org/pkg/container/heap/

package main

import (
       "fmt"
       "sort"
)
func solve() int {
     var D int
     fmt.Scan(&D)

     dishes := make([]int, D, D)
     
     for d := 0; d < D; d++ {
         fmt.Scan(&dishes[d])
     }
     sort.Sort(sort.Reverse(sort.IntSlice(dishes)))

     ret := dishes[0]
     for mx := 1; mx <= dishes[0]; mx++ {
         minutes := mx
         for _, dish := range dishes {
             minutes += (dish - 1) / mx
         }
         if minutes < ret {
             ret = minutes
         }
     }

     return ret
}

func main() {
     var T int
     fmt.Scan(&T)
     for t := 0; t < T; t++ {
          fmt.Printf("Case #%v: %v\n", t+1, solve())
     }
}
