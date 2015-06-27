#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,T = map(int,input().split())

A = []
for _ in range(N):
    A.append(int(input()))
A.reverse()

ans = 0
prev = 1e10
for a in A:
    duration = min(T, prev - a)
    ans += duration
    prev = a
print(ans)

    
