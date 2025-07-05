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


arr = []
i = 0
Q = int(input())
for q in range(Q):
    items = list(map(int, input().split()))
    if items[0] == 1:
        arr.append((items[1], items[2]))
    else:
        k = items[1]
        ans = 0
        while k > 0:
            if arr[i][0] == k:
                ans += arr[i][0] * arr[i][1]
                k = 0
                i += 1
            elif arr[i][0] > k:
                ans += k * arr[i][1]
                arr[i] = (arr[i][0] - k, arr[i][1])
                k = 0
            else:
                ans += arr[i][0] * arr[i][1]
                k -= arr[i][0]
                i += 1
        print(ans)


