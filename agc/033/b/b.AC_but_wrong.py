#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
本番中にAC、ただし嘘解法であることが判明
in_corner はNOにならないといけないのに、このコードはYESを返す

このコードの嘘解法：
上下方向と左右方向は独立に考えることができる。
高橋君は上方向に駒を落としたいとしたとき、
高橋君はなるべく上方向に駒を移動させ、
青木君はなるべく下方向に駒を移動させる。
もし駒を落とせるなら高橋君の勝ち。
これを4つの方向ですべて行う。
"""

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

H, W, N = map(int, input().split())
sr, sc =  map(int, input().split())
sr -= 1
sc -= 1

S = input()
T = input()

def solve2(sc, W, S, T, inc, dec):
    x = sc
    for s, t in zip(S, T):
        if s == inc:
            x += 1
            if x == W:
                return True
        if t == dec:
            x = max(x - 1, 0);

    x = sc
    for s, t in zip(S, T):
        if s == dec:
            x -= 1
            if x == -1:
                return True
        if t == inc:
            x = min(x + 1, W - 1);

    return False


def solve(H, W, N, sr, sc, S, T):
    res1 = solve2(sc, W, S, T, 'R', 'L')
    res2 = solve2(sr, H, S, T, 'D', 'U')
    return res1 or res2

    # x = sc
    # for s, t in zip(S, T):
    #     if s == 'R':
    #         x += 1
    #         if x == W:
    #             return True
    #     if t == 'L':
    #         x = max(x - 1, 0);

    # x = sc
    # for s, t in zip(S, T):
    #     if s == 'L':
    #         x -= 1
    #         if x == -1:
    #             return True
    #     if t == 'R':
    #         x = min(x + 1, W - 1);


            


res = solve(H, W, N, sr, sc, S, T)
if res:
    print('NO')
else:
    print('YES')

