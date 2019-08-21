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

N = 2 * 10 ** 5
print(N)
As = [0] * N
for n in range(N):
    As[n] = random.randint(1, 10)

Bs = As[:]
fail = 0
while fail < 1e8:
    i = random.randint(0, N - 1)
    if i == N - 1:
        j = 0
    else:
        j = i + 1

    nxt = Bs[i-1] + Bs[i] + Bs[j]
    if nxt >= 10 ** 9:
        fail += 1
        continue
    else:
        fail = 0
        Bs[i] = nxt

print(*As)
print(*Bs)


