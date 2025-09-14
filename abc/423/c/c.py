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

LOCKED = 1
UNLOCKED = 0

def solve(N, R, L):

    if min(L) == max(L) == 1:
        return 0

    s = "".join(str(i) for i in L)

    start_i = s.find("0")
    end_i = s.rfind("0")
    # print(start_i, end_i)

    tmp_ans = L[start_i:end_i+1].count(1) + (end_i - start_i + 1)
    
    if R < start_i:
        tmp_ans += (start_i - R) * 2
    if R >= end_i + 2:
        tmp_ans += (R - end_i - 1) * 2

    return tmp_ans


N, R  = map(int, input().split())
L = list(map(int, input().split()))

print(solve(N, R, L))




