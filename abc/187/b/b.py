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

N = int(input())
XYs = []
for n in range(N):
    x, y = map(int, input().split())
    XYs.append((x, y))

ans = 0
for n in range(N - 1):
    for m in range(n + 1, N):
        x1, y1 = XYs[n]
        x2, y2 = XYs[m]

        nu = y2 - y1
        de = x2 - x1

        if de > 0:
            ans += -de <= nu <= de
        else:
            ans += de <= nu <= -de

print(ans)




