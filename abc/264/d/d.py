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




s = "atcoder"
ch2i = dict()
for i, ch in enumerate(s):
    ch2i[ch] = i

S = input()
arr = [ch2i[ch] for ch in S]

# https://www.geeksforgeeks.org/number-swaps-sort-adjacent-swapping-allowed/
N = len(S)
cnt = 0
for i in range(N - 1):
    for j in range(i + 1, N):
        cnt += arr[i] > arr[j]
print(cnt)





