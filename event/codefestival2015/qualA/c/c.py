#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,T = map(int,input().split())

diffs = []
s = 0
for _ in range(N):
    a,b = map(int,input().split())
    diffs.append(a-b)
    s += a

diffs.sort()
diffs.reverse()

idx = 0
while s > T and idx < N:
    s -= diffs[idx]
    idx += 1
if s > T:
    print(-1)
else:
    print(idx)

