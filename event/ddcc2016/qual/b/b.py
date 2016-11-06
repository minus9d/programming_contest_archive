#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

R,N,M = map(int,input().split())

def getlen(i):
    if i <= 0 or i >= N:
        return 0
    if i >= N // 2:
        i = N - i
    unit = 2 * R / N
    y = R - unit * i
    return math.sqrt(R ** 2 - y ** 2) * 2

ans = 0.0
for n in range(1, N+M):
    m = n - M
    ans += max(getlen(n), getlen(m))
print("{0:.15f}".format(ans))
