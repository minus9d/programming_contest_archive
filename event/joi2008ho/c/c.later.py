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
Ps = []
for n in range(N):
    Ps.append(int(input()))
Ps.append(0)

seen1 = set()
for p0 in Ps:
    for p1 in Ps:
        seen1.add(p0 + p1)

seen2 = list(seen1)
seen2.sort()

ans = 0
for p in seen1:
    if p > M:
        continue

    mx = M - p

    idx = bisect_left(seen2, mx + 1)
    if idx != 0:
        p += seen2[idx - 1]
    ans = max(ans, p)

print(ans)

