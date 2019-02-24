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

N, A, B, C = map(int, input().split())
Ls = [None] * N
for n in range(N):
    Ls[n] = int(input())

ans = 1e9
group = [0, 1, 2, 3]
for comb in product(group, repeat=N):
    c = Counter()
    tmp = 0
    for i, group_idx in enumerate(comb):
        if group_idx == 3:
            continue
        if c[group_idx] != 0:
            tmp += 10
        c[group_idx] += Ls[i]
    if c[0] == 0 or c[1] == 0 or c[2] == 0:
        continue
    tmp += abs(c[0] - A)
    tmp += abs(c[1] - B)
    tmp += abs(c[2] - C)
    ans = min(ans, tmp)
print(ans)
