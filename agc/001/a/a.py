#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
Ls = list(map(int,input().split()))
Ls.sort()
ans = 0
for i in range(N):
    ans += Ls[i*2]
print(ans)
