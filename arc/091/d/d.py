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

N, K = map(int, input().split())
if K == 0:
    print(N * N)



for n in range(1, 100):
    print("n:", n)
    c = Counter()
    for a in range(1, n+1):
        for b in range(1,n+1):
            c[a % b] += 1
    for k in sorted(c.keys()):
        print(k, c[k])
    print("")
    for m in range(n):
        s = 0
        for i in range(m, n):
            s += c[i]
        print("{} or more: {}".format(m, s))
    print("")

