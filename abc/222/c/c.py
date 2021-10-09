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


N, M  = map(int, input().split())
cells = []
for i in range(N * 2):
    As = input()
    cells.append(As)

arr = []
for n in range(N * 2):
    arr.append((0, n))

def win(p1, p2, m):
    hand1 = cells[p1[1]][m]
    hand2 = cells[p2[1]][m]

    comb = [('G', 'C'), ('C', 'P'), ('P', 'G')]
    for h1, h2 in comb:
        if hand1 == h1 and hand2 == h2:
            return True
    return False


for m in range(M):
    new_arr = []
    for n in range(N):
        p1 = arr[n * 2]
        p2 = arr[n * 2 + 1]
        if win(p1, p2, m):
            new_arr.append((p1[0] + 1, p1[1]))
            new_arr.append(p2)
        elif win(p2, p1, m):
            new_arr.append((p2[0] + 1, p2[1]))
            new_arr.append(p1)
        else:
            new_arr.append(p1)
            new_arr.append(p2)
    new_arr.sort(key=lambda item: (-item[0], item[1]))
    arr = new_arr
    # print(arr)

for a in arr:
    print(a[1] + 1)
