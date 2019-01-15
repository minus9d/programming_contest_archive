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
Xs = list(map(int, input().split()))

minus = []
plus = []
for x in Xs:
    if x < 0:
        minus.append(x)
    elif x == 0:
        K -= 1
    else:
        plus.append(x)

# 左にあるn個を取るまでの移動距離
left_dist = [0] * (len(minus) + 1)
for i, m in enumerate(reversed(minus)):
    left_dist[i+1] = abs(m)
# 右にあるn個を取るまでの移動距離
right_dist = [0] * (len(plus) + 1)
for i, p in enumerate(plus):
    right_dist[i+1] = p
# print(left_dist)
# print(right_dist)

ans = 1e20
for left_num in range(0, K + 1):
    right_num = K - left_num
    if left_num > len(minus) or right_num > len(plus):
        continue
    ans = min(ans, left_dist[left_num] * 2 + right_dist[right_num])
    ans = min(ans, right_dist[right_num] * 2 + left_dist[left_num])
print(ans)
