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

N = int(input())
As = list(map(int, input().split()))
Bs = list(map(int, input().split()))


def solve(N, As, Bs):
    A_sum = sum(As)
    B_sum = sum(Bs)
    if A_sum < B_sum:
        return -1
    margin = A_sum - B_sum
    
    ans = 0
    need = 0
    extra = []
    for a, b in zip(As, Bs):
        if b > a:
            need += b - a
            ans += 1
        elif a > b:
            extra.append(a - b)
    extra.sort()
    extra.reverse()
    i = 0
    while need > 0:
        need -= extra[i]
        i += 1
        ans += 1
    return ans

print(solve(N, As, Bs))    



