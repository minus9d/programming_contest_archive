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
A = list(map(int, input().split()))
B = list(map(int, input().split()))

A.sort()
B.sort()

ok = True
a_idx = b_idx = 0
ans = 0
for b in B:
    try:
        while A[a_idx] < b:
            a_idx += 1
        ans += A[a_idx]
        a_idx += 1
    except IndexError:
        ok = False
        break

if ok:
    print(ans)
else:
    print(-1)




