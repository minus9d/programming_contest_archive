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
f_to_s_list = defaultdict(list)
for n in range(N):
    f, s = map(int, input().split())
    f_to_s_list[f].append(s)

ans = 0
for f, s_list in f_to_s_list.items():
    if len(s_list) >= 2:
        s_list.sort(reverse=True)
        ans = max(ans, s_list[0] + s_list[1] // 2)

best = []
for f, s_list in f_to_s_list.items():
    best.append(max(s_list))
best.sort(reverse=True)

if len(best) >= 2:
    ans = max(ans, sum(best[:2]))

print(ans)
