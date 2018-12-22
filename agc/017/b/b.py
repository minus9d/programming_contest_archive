#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

N, A, B, C, D = map(int, input().split())
diff = B - A
if diff < 0:
    diff *= -1

def can_reach(k, M):
    if k < 0:
        return False
    mx = M * D
    mn = M * C
    m = (M - k) // 2

    mx -= (D + C) * m
    mn -= (D + C) * m

    # print("diff, M, k, mn, mx = ", diff, M, k, mn, mx)
    return mn <= diff <= mx

flag = False
if N % 2 == 1:
    for k in range(0, N+1, 2):
        if can_reach(k, N - 1):
            flag = True
else:
    for k in range(1, N+1, 2):
        if can_reach(k, N - 1):
            flag = True
if flag:
    print("YES")
else:
    print("NO")
