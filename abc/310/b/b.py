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


N, M  = map(int, input().split())
P = []
C = []
F = []
for n in range(N):
    tmp = list(map(int, input().split()))
    p, c, f = tmp[0], tmp[1], tmp[2:]
    P.append(p)
    C.append(c)
    F.append(set(f))

ans = 'No'
for i in range(N):
    for j in range(N):
        if i == j: continue
        cond1 = P[i] >= P[j]
        cond2 = F[j] >= F[i]
        cond3 = P[i] > P[j] or F[j] > F[i]
        if all([cond1, cond2, cond3]):
            ans = 'Yes'
print(ans)

