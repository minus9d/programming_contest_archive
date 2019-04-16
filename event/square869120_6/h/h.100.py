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


def choose(n, k):
    ret = 1
    for i in range(k):
        ret *= (n - i)
    for i in range(k):
        ret //= (i + 1)
    return ret

table = [None] * 129
for i in range(1, 129):
    n = 0
    for j in range(1, i + 1):
        n += choose(i, j)
    table[i] = n

Q = int(input())
for q in range(Q):
    ans = []
    head = 1
    K = int(input())
    K -= 1
    while K > 0:
        use = -1
        for i in range(128, -1, -1):
            if table[i] <= K:
                use = i
                break
        K -= table[use]
        ans = list(range(head, head + use)) + ans
        head += use
    print(len(ans), *ans)
