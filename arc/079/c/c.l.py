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

# 実はdicts[0], dicts[N-1]だけあれば十分
dicts = [set() for _ in range(N)]
for m in range(M):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    dicts[a].add(b)
    dicts[b].add(a)

# 島1 -> どこかの島 -> 島Nというルートが可能
if dicts[0] & dicts[N-1]:
    print('POSSIBLE')
else:
    print('IMPOSSIBLE')
