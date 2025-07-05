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
S = []
for n in range(N):
    S.append(input())

seen = set()
for i in range(N):
    for j in range(N):
        if i != j:
            tmp = S[i] + S[j]
            seen.add(tmp)
print(len(seen))
