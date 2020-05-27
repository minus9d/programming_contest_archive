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


def solve():
    U = int(input())

    QR = []
    for rep in range(10000):
        q, r = input().split()
        q = int(q)
        QR.append((q, r))

    letters = set()
    table = defaultdict(set)
    for q, r in QR:
        if len(str(q)) == len(r):
            table[str(q)[0]].add(r[0])
        for ch in r:
            letters.add(ch)
    # print(table)
    # print(letters)

    decided = set()    
    ans = {}
    for digit in range(1, 10):
        candidates = table[str(digit)]
        for c in candidates:
            if c in decided:
                continue
            else:
                ans[digit] = c
                decided.add(c)

    for letter in letters:
        if letter not in decided:
            ans[0] = letter
            break

    # print(ans)
    ans2 = ""
    for digit in range(10):
        ans2 += ans[digit]
    print(ans2)
        

        


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
