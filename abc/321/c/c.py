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


seen = []

def dfs(i, arr):
    seen.append(arr + [i])
    for j in range(i):
        dfs(j, arr + [i])

for i in range(1, 10):
    dfs(i, [])

seen2 = []
for arr in seen:
    tmp = ''.join(str(x) for x in arr)
    seen2.append(int(tmp))

seen2.sort()


K = int(input())
print(seen2[K - 1])


