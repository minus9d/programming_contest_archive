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

N, M = map(int, input().split())

ABs = []
for n in range(N):
    a, b = map(int, input().split())
    ABs.append((a, b))

ABs.sort()
ans = 0
for a, b in ABs:
    num = min(b, M) 
    ans += num * a
    M -= num
print(ans)
