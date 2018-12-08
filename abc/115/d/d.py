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

N, X = map(int, input().split())

all_elements = [1]
ps = [1]
bs = [0]
for i in range(50):
    all_elements.append(all_elements[-1] * 2 + 3)
    ps.append(ps[-1] * 2 + 1)
    bs.append(bs[-1] * 2 + 2)

def from_bottom(n, x):
    if n == 0:
        if x == 1: return 1
        else: return 0

    curr_elements = all_elements[n]
    prev_elements = all_elements[n - 1]

    if x <= 1:
        return 0
    if x <= prev_elements + 1:
        return from_bottom(n - 1, x - 1)
    if x == prev_elements + 1:
        return from_bottom(n - 1, x - 2) + 1
    if x <= prev_elements * 2 + 2:
        return 1 + ps[n - 1] + from_bottom(n - 1, x - 2 - prev_elements)
    if x == curr_elements:
        return ps[n]

def slow(n, x):
    burger = ['P']
    for i in range(n):
        burger = ['B'] + burger + ['P'] + burger + ['B'] 
    # print(burger)
    ans = 0
    for i in range(x):
        ans += burger[i] == 'P'
    return ans

# # debug
# while True:
#     for n in range(2, 50):
#         for x in range(6, all_elements[n]):
#             if from_bottom(n, x) != slow(n, x):
#                 print("error! n, x = ", n, x )
#                 print("wrong:", from_bottom(n, x))
#                 print("correct:", slow(n, x))
#                 sys.exit(0)

print(from_bottom(N, X))
