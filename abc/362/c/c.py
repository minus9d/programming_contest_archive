#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq
from itertools import *
import math
import random
import re
import string
import sys


sys.setrecursionlimit(10 ** 9)


N = int(input())

LR = []
minus = []
plus = []
plus_minus = []
for n in range(N):
    l, r = map(int, input().split())
    LR.append((l, r))
    if r < 0:
        minus.append((l, r))
    elif l > 0:
        plus.append((l, r))
    else:
        plus_minus.append((l, r))

# 全部Rを選んで、大きすぎたら調整していく
def solve(N, LR):
    ans = []
    s = 0
    for l, r in LR:
        ans.append(r)
        s += r

    if s < 0:
        print('No')
        return

    # print("s = ", s)
    for i in range(N):
        l, r = LR[i]
        can_move = r - l
        if can_move >= s:
            r -= s
            s = 0
            ans[i] = r
            break
        else:
            ans[i] = l
            s -= can_move
    
    # print("s = ", s)
    if s > 0:
        print('No')
        return

    print('Yes')
    print(*ans)

solve(N, LR)
sys.exit(0)

# print("minus:", minus)
# print("plus:", plus)
# print("pm:", plus_minus)

# mn_min = 0
# mn_max = 0
# for l, r in minus:
#     mn_min += l
#     mn_max += r
# print(f"minus: {mn_min} to {mn_max}")

# pl_min = 0
# pl_max = 0
# for l, r in plus:
#     pl_min += l
#     pl_max += r
# print(f"plus: {pl_min} to {pl_max}")

# diff_max = pl_max + mn_max
# diff_min = pl_min + mn_min
# print(f"diff: {diff_min} to {diff_max}")

# plus_minus_min = 0
# plus_minus_max = 0
# for l, r in plus_minus:
#     plus_minus_min += l
#     plus_minus_max += r
# print(f"plus_minus: {plus_minus_min} to {plus_minus_max}")

