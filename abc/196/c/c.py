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

def solve_fast(N):
    i = 1
    ans = 0
    while True:
        s = str(i)
        num = int(s + s)
        if num <= N:
            ans += 1
        else:
            break
        i += 1
    return ans

def solve_slow(N):
    cnt = 0
    for i in range(1, N + 1):
        s = str(i)
        if len(s) % 2 == 1:
            continue
        size = len(s)
        a = s[:size // 2]
        b = s[size // 2:]
        if a == b:
            cnt += 1
    return cnt

# for i in range(10000):
#     print(i)
#     assert solve_slow(i) == solve_fast(i), "{}, {}".format(solve_slow(i), solve_fast(i))

N = int(input())
print(solve_fast(N))

