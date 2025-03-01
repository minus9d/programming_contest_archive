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

ans = [['?' for _ in range(N)] for _ in range(N)]


sign = '#'
for n in range((N + 1) // 2):
    for y in range(N):
        for x in range(N):
            if ((x in [n, N - n - 1] and n <= y <= N - n - 1)
                or (y in [n, N - n - 1] and n <= x <= N - n - 1)):
                ans[y][x] = sign
    sign = '.' if sign == '#' else '#'

    # print("===" * 10)
    # for a in ans:
    #     print(''.join(a))
    # # print(sign)

for a in ans:
    print(''.join(a))

