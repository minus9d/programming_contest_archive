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


N, M, K = map(int, input().split())

arr = [[0] * M for _ in range(N)]
# print(arr)

ans = []
for k in range(K):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    arr[a][b] = 1
    if min(arr[a]) == 1:
        ans.append(a + 1)

if ans:
    print(*ans)
