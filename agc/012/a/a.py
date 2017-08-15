#!/usr/bin/env python3

N = int(input())
As = list(map(int, input().split()))
As.sort()
As.reverse()

ans = 0
for n in range(N):
    ans += As[n * 2 + 1]
print(ans)

