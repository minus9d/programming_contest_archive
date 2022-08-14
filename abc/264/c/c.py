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


H1, W1  = map(int, input().split())
A = []
for h in range(H1):
    A.append(list(map(int, input().split())))


H2, W2  = map(int, input().split())
B = []
for h in range(H2):
    B.append(list(map(int, input().split())))

from pprint import pprint
ans = False
for i in range(1 << H1):

    cnt = 0
    for k in range(H1):
        if ((1 << k) & i): cnt += 1
    if cnt != H2:
        continue

    tmp = []
    for k in range(H1):
        if ((1 << k) & i):
            tmp.append(A[k])
    
    # pprint(tmp)
    # print()

    for j in range(1 << W1):

        cnt2 = 0
        for k in range(W1):
            if ((1 << k) & j): cnt2 += 1
        if cnt2 != W2:
            continue

        tmp2 = []
        for line in tmp:
            line2 = []
            for k in range(W1):
                if ((1 << k) & j):
                    line2.append(line[k])
            tmp2.append(line2)

        # print("tmp2:")
        # pprint(tmp2)
        # print("B:")
        # pprint(B)
        # print()

        def same(a1, a2):
            assert len(a1) == len(a2)
            for l1, l2 in zip(a1, a2):
                if tuple(l1) != tuple(l2):
                    return False
            return True

        if same(B, tmp2):
            ans = True
            break

if ans:
    print('Yes')
else:
    print('No')
