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

N, D = map(int, input().split())
X = list(map(int, input().split()))

c = Counter(X)
pos = sorted(list(set(X)))
ans = 1e9
for i in range(len(pos)):
    for j in range(i, len(pos)):
        xi = pos[i]
        yi = pos[j]
        d = yi - xi
        if d <= D:
            men_num = 0
            for k in range(i, j + 1):
                men_num += c[pos[k]]
            ans = min(ans, N - men_num)
print(ans)
        
