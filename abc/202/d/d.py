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

fact = []
fact.append(1)
tmp = 1
for i in range(1, 61):
    tmp *= i
    fact.append(tmp)

def get_comb(a, b):
    return fact[a + b] // fact[a] // fact[b] 


# https://stackoverflow.com/questions/4223349/python-implementation-for-next-permutation-in-stl
def next_permutation(a):
    """Generate the lexicographically next permutation inplace.

    https://en.wikipedia.org/wiki/Permutation#Generation_in_lexicographic_order
    Return false if there is no next permutation.
    """
    # Find the largest index i such that a[i] < a[i + 1]. If no such
    # index exists, the permutation is the last permutation
    for i in reversed(range(len(a) - 1)):
        if a[i] < a[i + 1]:
            break  # found
    else:  # no break: not found
        return False  # no next permutation

    # Find the largest index j greater than i such that a[i] < a[j]
    j = next(j for j in reversed(range(i + 1, len(a))) if a[i] < a[j])

    # Swap the value of a[i] with that of a[j]
    a[i], a[j] = a[j], a[i]

    # Reverse sequence from a[i + 1] up to and including the final element a[n]
    a[i + 1:] = reversed(a[i + 1:])
    return True


def solve_slow(a, b, k):
    arr = ['a'] * a + ['b'] * b

    appear = []
    appear.append(''.join(arr))
    while next_permutation(arr):
        appear.append(''.join(arr))

    return appear[k - 1]

def solve(a, b, k):
    if a == 0:
        return 'b' * b

    if b == 0:
        return 'a' * a

    # aで始まる
    val1 = get_comb(a - 1, b)
    if k <= val1:
        return 'a' + solve(a - 1, b, k)
    else:
        return 'b' + solve(a, b - 1, k - val1)


A, B, K = map(int, input().split())

# for a in range(1, 5):
#     for b in range(1, 5):
#         mx = get_comb(a, b)
#         for k in range(1, mx):
#             mine = solve(a, b, k)
#             gt = solve_slow(a, b, k)
#             if mine != gt:
#                 print("error")
#                 print(a, b, k, mine, gt)
#                 sys.exit(0)


print(solve(A, B, K))
# print(solve_slow(A, B, K))






