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

def is_valid(cells, h, w):
    ok = False
    dhs = [0, 1, -1, 0, 0]
    dws = [0, 0, 0, 1, -1]
    for (dh, dw) in zip(dhs, dws):
        h2 = h + dh
        w2 = w + dw
        # 配列に負の値を入れてWA
        if 0 <= h2 < N and 0 <= w2 < N and cells[h2][w2] == 1:
            ok = True
    return ok


def solve(N):
    
    cells = [[0 for n in range(N)] for _ in range(N)]
    
    s = 0
    for h in range(N):
        for w in range(N):
            if (s + w) % 5 == 0:
                cells[h][w] = 1
        s = (s + 2) % 5
    
    for h in range(N):
        for w in range(N):
            if not is_valid(cells, h, w):
                cells[h][w] = 1

    return cells


# test
# for N in range(1000, 10, -1):
    # cells = solve(N)
    # used = sum(sum(x for x in row) for row in cells)
    # print()
    # print("N, used = ", N, used)
    # for r in cells: print(r)
    # if used > 201800:
    #     print("wrong!! N = ", N)
    #     sys.exit(0)

    # for h in range(N):
    #     for w in range(N):
    #         if not is_valid(cells, h, w):
    #             print("error!!!!")
    #             sys.exit(0)

N = int(input())
cells = solve(N)    
for row in cells:
    s = ''
    for e in row:
        if e == 1:
            s += 'X'
        else:
            s += '.'
    print(s)

