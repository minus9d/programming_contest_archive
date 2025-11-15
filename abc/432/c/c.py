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


def solve(N, X, Y, A):

    mod_list = []
    for a in A:
        mod_list.append((X * a) % (Y - X))
    if len(set(mod_list)) > 1:
        return -1

    for i, a in enumerate(A):
        if i == 0:
            mn = a * X
            mx = a * Y
        else:
            tmp_mn = a * X
            tmp_mx = a * Y
            
            mn = max(tmp_mn, mn)
            mx = min(tmp_mx, mx)
    
    if mn <= mx:
        ans = 0
        for a in A:
            ans += (mx - a * X) // (Y - X)
        return ans
    else:
        return -1


N, X, Y = map(int, input().split())
A = list(map(int, input().split()))
print(solve(N, X, Y, A))


