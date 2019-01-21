#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 終了後解いた
#
# 実験で答の末尾に9が並ぶことから、
# そのような解の候補を生成し、条件を満たすものを残しただけ。
# 証明は理解できていない…。
#
#


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

def T(k):
    orig_k = k
    sk = 0
    while k > 0:
        sk += k % 10
        k //= 10
    return orig_k / sk

d = {}
MAX = int(1e15) + 1e9
for i in range(1, 999):
    t = i
    while t < MAX:
        d[t] = T(t)
        t = t * 10 + 9

keys = sorted(list(d.keys()))

# for k in keys:
#     print(k, d[k])

mn = None
ans = []
for k in reversed(keys):
    if mn == None:
        ans.append(k)
        mn = d[k]
    else:
        if mn >= d[k]:
            ans.append(k)
            mn = min(mn, d[k])

ans.reverse()

K = int(input())
ans = ans[:K]
for a in ans:
    print(a)
