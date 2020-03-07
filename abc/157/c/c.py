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

rules = []
for m in range(M):
    rules.append(list(map(int, input().split())))

def ok(k):
    k_str = str(k)
    if N != len(k_str): return False
    for s, c in rules:
        if s > len(k_str): return False
        if int(k_str[s - 1]) != c: return False
    return True


ans = -1
for i in range(1000):
    if ok(i):
        ans = i
        break
print(ans)

