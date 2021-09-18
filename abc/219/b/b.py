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


strs = []
for _ in range(3):
    strs.append(input())

T = input()
ans = ""
for t in T:
    ans += strs[int(t) - 1]
print(ans)
