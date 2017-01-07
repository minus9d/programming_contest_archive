#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def func(k, n):
    if n <= k:
        return n + 1
    elif n <= 2 * k:
        return 2 * k - n + 1
    else:
        return 0

K,S = map(int,input().split())
ans = 0
for a in range(K+1):
    if S-a >= 0:
        ans += func(K, S-a)
print(ans)
