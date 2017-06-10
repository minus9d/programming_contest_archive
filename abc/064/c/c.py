#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

_ = input()
As = list(map(int, input().split()))
bins = [0] * 9
table = [400, 800, 1200, 1600, 2000, 2400, 2800, 3200, 10000]
for a in As:
    for i, t in enumerate(table):
        if a < t:
            bins[i] += 1
            break
mn = sum(1 for x in bins[:-1] if x > 0)
if mn == 0:
    mn = 1
    mx = bins[-1]
else:
    mx = mn + bins[-1]
print(mn, mx)


