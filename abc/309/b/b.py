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
src = []
for n in range(N):
    tmp = list(input())
    src.append(tmp)

import copy
dst = copy.deepcopy(src)

for i in range(N-1):
    dst[0][i+1] = src[0][i]
    dst[-1][i] = src[-1][i+1]
    dst[i+1][-1] = src[i][-1]
    dst[i][0] = src[i+1][0]

for d in dst:
    print(''.join(d))


