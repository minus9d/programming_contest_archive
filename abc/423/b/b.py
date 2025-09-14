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
L = list(map(int, input().split()))

ans = set([0, N])
for i in range(N):
    if L[i] == 0:
        ans.add(i + 1)
    else:
        break

for i in range(N-1, -1, -1):
    if L[i] == 0:
        ans.add(i)
    else:
        break

print(N + 1 - len(ans))


