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
As = list(map(int, input().split()))
S = set(As)

ans = []
arr = []
for i in range(1, N + 1):
    arr.append(i)
    if i not in S:
        while arr:
            ans.append(arr[-1])
            del arr[-1]
print(*ans)

