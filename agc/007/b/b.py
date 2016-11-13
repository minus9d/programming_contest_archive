#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
Ps = list(map(int,input().split()))

def solve(Ps):
    n = len(Ps)
    As = [x * 30000 + 1 for x in range(n)]
    Bs = list(reversed(As[:]))
    for i, p in enumerate(Ps):
        Bs[p-1] += i
    return As, Bs

As, Bs = solve(Ps)
print(*As)
print(*Bs)
