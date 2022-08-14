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

s = 15
arr = [[0] * s for j in range(s)]

for i in range(4):
    size = s - i * 4
    start = i * 2
    for j in range(size):
        arr[start][start + j] = 1
        arr[s - start - 1][start + j] = 1
        arr[start + j][start] = 1
        arr[start + j][s - start - 1] = 1

R, C = map(int, input().split())
if arr[R-1][C-1]:
    print('black')
else:
    print('white')

