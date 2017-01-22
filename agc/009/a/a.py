#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
As = []
Bs = []
for n in range(N):
    a, b = map(int, input().split())
    As.append(a)
    Bs.append(b)

As.reverse()
Bs.reverse()
offset = 0
for a, b in zip(As, Bs):
    a += offset
    if a % b != 0:
        offset += b - (a % b)
print(offset)        

