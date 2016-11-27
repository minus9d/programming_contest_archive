#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
s = 0
ans = set()
for i in range(1,N+1):
    s += i
    ans.add(i)
    if s == N:
        break
    if s > N:
        ans.remove(s - N)
        break
for a in ans:
    print(a)


