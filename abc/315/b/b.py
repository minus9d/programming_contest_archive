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


M = int(input())
Ds = list(map(int, input().split()))

s = sum(Ds)
idx = s // 2 + 1

for month_idx, d in enumerate(Ds):
    if idx <= d:
        month = month_idx + 1
        day = idx
        break
    else:
        idx -= d
print(month, day)

        



