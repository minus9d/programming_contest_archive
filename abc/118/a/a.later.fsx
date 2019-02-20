// 参考: https://qiita.com/kuuso1/items/606b75c172cafa1d07f6

open System

let inputArray = stdin.ReadLine().Split(' ') |> Array.map int
let a = inputArray.[0]
let b = inputArray.[1]

let f a b = if (b % a) = 0 then a + b else b - a

f a b |> printfn "%d"
