N = int(input())
s = input()
t = input()
for i in range(len(s)+1):
    if t.startswith(s[i:]):
        print(len(s[:i] + t))
        break

