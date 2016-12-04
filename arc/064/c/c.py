#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N,x = map(int,input().split())
As = list(map(int,input().split()))
Bs = As[:]
for i in range(1,N):
    s = As[i] + As[i-1]
    if s > x:
        As[i] = max(0, As[i] - (s - x))
    s = As[i] + As[i-1]
    if s > x:
        As[i-1] = As[i-1] - (s - x)
ans = sum(b - a for a, b in zip(As, Bs))
print(ans)

    
    
