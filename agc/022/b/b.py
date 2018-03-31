#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
from fractions import *
import heapq 
from itertools import *
import math
import random
import re
import string
import sys

N = int(input())

def is_valid(arr):
    size = len(arr)
    sumarr = sum(arr)
    if max(arr) > 30000:
        return False

    gcd_of_all = gcd(arr[0], arr[1])
    for i in range(2, size):
        gcd_of_all = gcd(gcd_of_all, arr[i])
    if gcd_of_all != 1:
        return False

    for i in range(size):
        n1 = arr[i]
        n2 = sumarr - n1
        if gcd(n1, n2) == 1:
            return False
    return True

def brute_force(SIZE):
    MAX = 50
    for comb in combinations(list(range(1,MAX+1)), SIZE):
        if is_valid(list(comb)):
            return list(comb)

# N = 41で死ぬ
def solve(N):
    if N <= 4:
        ans = brute_force(N)
    else:
        ans = [2, 3, 4, 5]
        cand = 6
        sumans = sum(ans)
        while (len(ans) < N - 1):
            if not (cand % 2 == 0 or cand % 3 == 0 or cand % 5 == 0):
                cand += 1
                continue
            if len(ans) == N - 2:
                if (sumans + cand) % 2 == 1:
                    cand += 1
                    continue
            ans.append(cand)
            sumans += cand
            cand += 1

        ans.append(cand)
        while True:
            if is_valid(ans): break
            else: ans[-1] += 1
    # assert(is_valid(ans))
    return ans

print(*solve(N))

# # for debug
# for N in range(3, 20001):
#     ans = solve(N)
#     print("N {}: ok".format(N))
#     is_valid(ans)

# arr = list(range(1, 6000))
# while True:
#     random.shuffle(arr)
#     arr2 = arr[:3000]
#     if is_valid(arr2):
#         print("valid!", arr2)
#     else:
#         print("not valid")
    


# for a in range(1, MAX):
#     for b in range(a+1, MAX):
#         for c in range(b+1, MAX):
#             numset = [a,b,c]
#             if is_valid(numset):
#                 print(numset)
