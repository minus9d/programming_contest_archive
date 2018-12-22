#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
本番中解けず
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

N = int(input())
As = list(map(int, input().split()))

def solve_slow(N, As):
    """位置iを固定してその前後をシミュレート"""
    ans = 1e100
    for i in range(N):
        local_ans = 0
        a = As[i]
        for j in range(i+1, N):
            b = As[j]
            while b < a:
                b *= 4
                local_ans += 2
            a = b

        a = As[i]
        for j in range(i-1, -1, -1):
            b = As[j]
            while b > a:
                b *= -2
                local_ans += 1
            a = b
        ans = min(ans, local_ans)
    return ans

def solve(N, As):
    """実装途中、アイデアなし"""

    table = []
    muls = [0] * N
    divs = [0] * N
    for i in range(1, N):
        prev = As[i-1]
        curr = As[i]
        
        mul = 1
        while prev > curr * mul:
            mul *= 4
        muls[i] = mul

        div = 1
        while curr > prev * div:
            div *= 4
        divs[i] = div

    print(muls)
    print(divs)

    

print(solve_slow(N, As))
#print(solve(N, As))
