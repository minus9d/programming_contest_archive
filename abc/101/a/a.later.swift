let s = Array(readLine()!.characters)
var ans = 0
for i in 0...3 {
  ans += s[i] == Character("+") ? 1 : -1
}
print(ans)
