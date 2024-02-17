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


def getGcdSimple(a, b):
    if b == 0:
        return a
    return getGcdSimple(b, a % b)

def getLcmSimple(a, b):
    return a // getGcdSimple(a, b) * b


def solve_fast2(N, M, K):
    lcm = getLcmSimple(N, M)
    low = 0
    high = 10 ** 19

    while high - low > 1:
        k = (low + high) // 2
        cnt = k // N + k // M - (k // lcm * 2)
        if (cnt >= K):
            high = k
        else:
            low = k
    return high

N, M, K  = map(int, input().split())
print(solve_fast2(N, M, K))
