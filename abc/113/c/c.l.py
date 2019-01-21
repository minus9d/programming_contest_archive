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

N, M = map(int, input().split())
YPIs = []
for m in range(M):
    p, y = map(int, input().split())
    YPIs.append((y, p, m))
YPIs.sort()

ans = [None] * M
ctr = Counter()
for y, p, idx in YPIs:
    ans[idx] = "{:06d}{:06d}".format(p, ctr[p] + 1)
    ctr[p] += 1
for a in ans:
    print(a)




