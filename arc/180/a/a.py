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
S = input()

prev = None
chunk = ''
strings = []
for ch in S:
  if prev == ch:
    strings.append(chunk)
    chunk = ch
  else:
    chunk += ch
  prev = ch
strings.append(chunk)

ans = 1
for s in strings:
  ans *= (len(s) + 1) // 2
  ans %= (10 ** 9 + 7)

print(ans)
