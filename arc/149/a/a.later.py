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

N, M = [int(x) for x in input().split()]

ans = (-1, -1)
for i in range(1, 10):
    tmp = 0
    for j in range(N):
        tmp = tmp * 10 % M
        tmp = (tmp + i) % M
        if tmp == 0:
            ans = max(ans, (j, i))

if ans == (-1, -1):
    print(-1)
else:
    print(str(ans[1]) * (ans[0] + 1))
