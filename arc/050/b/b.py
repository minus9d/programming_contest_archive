#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

R,B = [int(x) for x in input().split()]
x,y = [int(x) for x in input().split()]

def check(k):
    red = R - k
    blue = B - k
    if red < 0 or blue < 0:
        return True
    can = red//(x-1) + blue//(y-1)
    return can < k

lo = 0
hi = int(1e20)
while lo < hi:
    k = (lo + hi) // 2
    res = check(k)
    if res:
        hi = k
    else:
        lo = k + 1

print(max(0,lo-1))
