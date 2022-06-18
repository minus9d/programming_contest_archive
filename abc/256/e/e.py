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


def solve(N, X, C):
    parents = [set() for _ in range(N)]
    for i in range(N):
        x = X[i]
        parents[x].add(i)

    removed = [0] * N
    
    # 順番にノードを消していく
    def delete_leaf(i):
        # print(f"delete_leaf({i}) is called")
        if not parents[i] and not removed[i]:  # iはleaf
            x = X[i]
            # print(f"  parents[{x}].remove({i})")
            parents[x].remove(i)
            removed[i] = 1
            delete_leaf(x)

    for i in range(N):
        delete_leaf(i)
    
    
    # 残った閉路について値最小のを選ぶ
    def get_min_val(i, first, mn_val):
#        print("i, first = ", i, first)
        mn_val = min(mn_val, C[i])
        next_i = X[i]
        C[i] = 0
        if next_i == first:
            return mn_val
        else:
            return get_min_val(next_i, first, mn_val)
    
    ans = 0
    for i in range(N):
        if parents[i] and C[i] > 0:
            # print("here.")
            ans += get_min_val(X[i], i, C[i])
            C[i] = 0
    return ans


# random.seed(1)
# while True:
#     N = 100000
#     X = list(range(N))
#     for n in range(N):
#         while True:
#             X[n] = random.randint(0, N - 1)
#             if X[n] != n:
#                 break
        
#     C = [random.randint(1, 4) for _ in range(N)]
#     # print("=" * 30)
#     # print(N)
#     # print(X)
#     # print(C)
#     print(solve(N, X, C))
# sys.exit(0)



N = int(input())
X = list(map(int, input().split()))
X = [x - 1 for x in X]
C = list(map(int, input().split()))
print(solve(N, X, C))








