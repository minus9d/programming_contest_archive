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

N, K = map(int, input().split())
Hs = []
for n in range(N):
    Hs.append(int(input()))
Hs.sort()

diff_min = 1e10
for i in range(N - (K - 1)):
    j = i + (K - 1)
    x = Hs[i]
    y = Hs[j]
    mn = min(x, y)
    mx = max(x, y)
    diff = mx - mn
    if diff < diff_min:
        diff_min = diff
print(diff_min)

    
