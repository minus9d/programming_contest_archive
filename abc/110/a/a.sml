(* 参考: https://beta.atcoder.jp/contests/abc109/submissions/3164770 *)
 
fun readInt () =
  TextIO.scanStream (Int.scan StringCvt.DEC) TextIO.stdIn
 
val SOME a = readInt ()
val SOME b = readInt ()
val SOME c = readInt ()
 
val ans1 = 10 * a + b + c
val ans2 = 10 * b + a + c
val ans3 = 10 * c + a + b
 
fun max(a,b) = if a>b then a else b;
 
val () =
  print (Int.toString(max(max(ans1, ans2), ans3)))
