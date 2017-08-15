from collections import *

N = int(input())
c = Counter()
for i, _ in enumerate(range(N)):
    s = input()
    c2 = Counter()
    for ch in s:
        c2[ch] += 1

    if i == 0:
        c = c2
    else:
        c_new = Counter()
        for k, v in c.items():
            c_new[k] = min(v, c2[k])
        c = c_new

ans = ''
for k in sorted(c.keys()):
    ans += k * c[k]
print(ans)
