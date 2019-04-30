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

def get_sum(s):
    return sum([int(x) for x in s])

def slow(N):
    target = get_sum(str(N))
    cand = 1
    while True:
        if get_sum(str(cand)) == target and cand != N:
            return cand
        cand += 1



def greedy(N):
    """ d9* というタイプの解を生成。dは1~9 """
    s = get_sum(str(N))
    nums = []
    while s > 0:
        if s >= 9:
            nums.append(9)
            s -= 9
        elif s == 0:
            break
        else:
            nums.append(s)
            break
    nums.reverse()
    return int("".join(str(x) for x in nums))


def fast(N):
    greedy_ans = greedy(N)
    if N != greedy_ans:
        return greedy_ans

    N_str = str(N)

    # 9...9のタイプ
    if min(N_str) == '9':
        return int('18' + '9' * (len(N_str) - 1))
    # dのタイプ (d = 1..8)
    elif len(N_str) == 1:
        return int('1' + str(N - 1))
    # d9...9のタイプ (d = 1..8)
    else:
        return int(str(int(N_str[0]) + 1) + 
                   str(int(N_str[1]) - 1) +
                   '9' * (len(N_str) - 2))

N = int(input())
# print(slow(N))
print(fast(N))
