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


N = int(input())
A = list(map(int, input().split()))
A.sort()

s = sum(A)
mn = s // N
remain = s - mn * N

B = [mn] * N
for i in range(remain):
    B[i] += 1
B.sort()
# print(A)
# print(B)

ans = 0
for a, b in zip(A, B):
    if a < b:
        ans += b - a
print(ans)




