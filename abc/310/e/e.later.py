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
S_ = input()
N = len(S_)  # for debug
S = [int(i) for i in S_]

zero = 0
one = 0
ans = 0
for s in S:
    if s == 0:
        zero, one = 1, zero + one
    else:
        zero, one = one, zero + 1
    ans += one
print(ans)

# 下は可視化
# ans = [[0 for i in range(N)] for j in range(N)]
# for i in range(N):
#     for j in range(i, N):
#         if i == j:
#             ans[i][j] = int(S[i])
#         else:
#             ans[i][j] = int(not(ans[i][j-1] and S[j]))
# print(S)
# print("====")
# for a in ans:
#     print(a)
