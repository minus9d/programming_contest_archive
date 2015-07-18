#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

N = int(input())
child = [[] for n in range(N)]
for n in range(N-1):
    idx = int(input()) - 1
    child[idx].append(n+1)

@functools.lru_cache(maxsize = None)
def money(idx):
    if len(child[idx]) == 0:
        return 1
    else:
        mn = 1e10
        mx = -1
        for c in child[idx]:
            m = money(c)
            mn = min(mn, m)
            mx = max(mx, m)
        return mn + mx + 1

print(money(0))    





