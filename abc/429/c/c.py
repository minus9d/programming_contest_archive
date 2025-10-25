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
A = list(map(int, input().split()))

c = Counter(A)
# print(c)

ans = 0
for k, v in c.items():
    ans += (v * (v - 1) // 2) * (N - v)
print(ans)
