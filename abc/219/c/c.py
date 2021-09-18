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


X = input()
N = int(input())

ch2num = {}
for i, ch in enumerate(X):
    ch2num[ch] = i

arr = []
for n in range(N):
    name1 = input()
    name2 = []
    for ch in name1:
        name2.append(ch2num[ch])
    arr.append((tuple(name2), name1))

arr.sort()
for n1, n2 in arr:
    print(n2)
