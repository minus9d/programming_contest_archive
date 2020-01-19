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

N = int(input())

def brute(N):
    ans = []
    for a in range(1, N + 1):
        for b in range(1, N + 1):
            a2 = str(a)
            b2 = str(b)
            if a2[0] == b2[-1] and a2[-1] == b2[0]:
                ans.append((a, b))

    return ans

def faster(N):
    arr = defaultdict(list)
    c = Counter()
    for n in range(1, N + 1):
        s = str(n)
        first = s[0]
        last = s[-1]
        arr[first + last].append(n)
        c[first + last] += 1

    ans = 0
    for key in c:
        key2 = key[-1] + key[0]
        ans += c[key] * c[key2]

    for n in range(11, 100, 11):
        s = str(n)
        ans -= len(arr[n]) * len(arr[n])

    return ans

print(faster(N))

# for n in range(1, 1000):
#     b = len(brute(n))
#     f = faster(n)
#     if b != f:
#         print("error!")
#         print(b, f)
#         sys.exit(0)


            
