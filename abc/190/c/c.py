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

N, M = map(int, input().split())

ABs = []
for m in range(M):
    a, b = map(int, input().split())
    ABs.append((a, b))

K = int(input())
CDs = []
for k in range(K):
    c, d = map(int, input().split())
    CDs.append((c, d))

ans = 0
for i in range(1 << K):
    s = set()
    for j in range(K):
        c, d = CDs[j]
        if i & (1 << j):
            s.add(c)
        else:
            s.add(d)
    # print("s:", s)
    cnt = 0
    for a, b in ABs:
        if a in s and b in s:
            cnt += 1
    ans = max(ans, cnt)

print(ans)
            
