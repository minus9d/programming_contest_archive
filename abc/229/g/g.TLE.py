#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
類題 https://tutorialspoint.com/program-to-find （YをN個連続させるのに必要な最小スワップ回数を求める）
を見つけたので、これを使って二分探索で解こうとしたが、TLE
類題のコードは理解していない

https://twitter.com/kyopro_friends/status/1464593018451750919
を参考にとき直すこと
"""

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

# https://www.tutorialspoint.com/program-to-find-minimum-adjacent-swaps-for-k-consecutive-ones-in-python
def calc_swap_num(nums, k):
   j = val = 0
   ans = 10 ** 100
   loc = []
   for i, x in enumerate(nums):
      if x:
         loc.append(i)
         m = (j + len(loc) - 1)//2
         val += loc[-1] - loc[m] - (len(loc)-j)//2
         if len(loc) - j > k:
            m = (j + len(loc))//2
            val -= loc[m] - loc[j] - (len(loc)-j)//2
            j += 1
         if len(loc)-j == k:
            ans = min(ans, val)
   return ans


def solve(S, K):
    nums = []
    for ch in S:
        if ch == 'Y':
            nums.append(1)
        else:
            nums.append(0)

    max_ans = sum(nums)

    # for i in range(1, max_ans + 1):
    #     print(i, calc_swap_num(nums, i))

    if max_ans == 0:
        return 0

    tmp = calc_swap_num(nums, max_ans)
    if tmp <= K:
        return max_ans

    lo = 1
    hi = max_ans
    while hi - lo > 1:
        mid = (lo + hi) // 2
        tmp = calc_swap_num(nums, mid)
        if tmp <= K:
            lo = mid
        else:
            hi = mid
    return lo

S = input()
K = int(input())
print(solve(S, K))
