#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from array import *
from bisect import *
from collections import *
from fractions import *
from heapq import *
from itertools import *
from math import *
from re import *
from string import *

# small
def solve():
    N, K = map(float, input().split())
    U = float(input())
    Ps = list(map(float, input().split()))
    c = Counter(Ps)
    while U > 0.0:
        new_c = Counter()
        if len(c) == 1:
            cur_amount, cur_num = list(sorted(c.items()))[0]
            given = U / cur_num
            new_c[cur_amount + given] = cur_num
            c = new_c
            break
        else:
            cur_items = list(sorted(c.items()))
            a0, n0 = cur_items[0]
            a1, n1 = cur_items[1]
            used_u = min(U, (a1 - a0) * n0)
            del c[a0]
            new_a0 = a0 + used_u / n0
            c[new_a0] += n0
            U -= used_u
        # print("now c, U, len(c):", c, U, len(c))
            
    p = 1.0
    for a, n in c.items():
        for n2 in range(n):
            p *= a
    print("{:.10f}".format(p))
    

T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
