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
XYZs = []
for n in range(N):
    x, y, z = map(int, input().split())
    XYZs.append((x,y,z))

ans = 0
for i in (1,-1):
    for j in (1,-1):
        for k in (1,-1):
            scores = []
            for x, y, z in XYZs:
                val = x * i + y * j + z * k
                scores.append(val)
            scores.sort()
            scores.reverse()
            ans = max(ans, sum(scores[:M]))
print(ans)

