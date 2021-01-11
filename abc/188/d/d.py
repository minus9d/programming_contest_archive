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

N, C = map(int, input().split())

arr = []
m = defaultdict(list)
for n in range(N):
    a, b, c = map(int, input().split())
    # arr.append((a, c))
    # arr.append((b + 1, -c))

    m[a].append(c)
    m[b + 1].append(-c)

arr.sort()

cur = 0
prev_day = -1
ans = 0
for day in sorted(m):
    costs = m[day]
    # print(day, costs)

    if prev_day == -1:
        prev_day = day
    else:
        if cur >= C:
            ans += (day - prev_day) * C
        else:
            ans += (day - prev_day) * cur

    prev_day = day
    # print("day {}: ans = {}".format(day, ans))

    cur += sum(costs)

print(ans)

    


