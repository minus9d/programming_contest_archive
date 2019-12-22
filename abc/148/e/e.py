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

def solve(N):
    if N % 2 == 1:
        return 0
    else:
        num_10 = N // 10

        k = 50
        num_5 = 0
        while k < 1e19:
            num_5 += N // k
            k *= 5

        return num_10 + num_5

# def brute(N):
#     s = 1
#     for n in range(N, 0, -2):
#         s *= n
    
#     st = reversed(str(s))
#     ans = 0
#     for ch in st:
#         if ch == '0':
#             ans += 1
#         else:
#             break
#     return ans

# for i in range(2, 252, 2):
#     print(i, brute(i))

# for i in range(1, 1000000):
#     ans = solve(i)
#     gt = brute(i)
#     if ans != gt:
#         print(i, ans, gt)
#         break

print(solve(N))    


