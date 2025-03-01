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

seen = {}

ans = 1e10
for i, a in enumerate(A):
    if a in seen:
        ans = min(ans, i - seen[a] + 1)
    seen[a] = i

if ans == 1e10:
    print(-1)
else:
    print(ans)
