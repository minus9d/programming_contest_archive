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


N, D  = map(int, input().split())
S = []
for n in range(N):
    s = input()
    S.append(s)

cont = 0
ans = 0
for d in range(D):
    ok = True
    for n in range(N):
        if S[n][d] == 'x':
            ok = False
            break
    if ok:
        cont += 1
        ans = max(ans, cont)
    else:
        cont = 0
print(ans)
