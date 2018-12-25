#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,M = map(int,input().split())

red = set([1])
pos = [0] + [1] * N
for m in range(M):
    x,y = map(int,input().split())
    if x in red:
        red.add(y)
        if pos[x] == 1:
            red.remove(x)
    pos[x] -= 1
    pos[y] += 1
        
print(len(red))
