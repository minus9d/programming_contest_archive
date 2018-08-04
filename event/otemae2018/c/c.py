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

def count(s, i):
    s2 = s.replace('.' * i, '')
    return (len(s) - len(s2)) // i

N, H, W = map(int, input().split())
cells = []
for h in range(H):
    cells.append(input())
for i in range(1, N+1):
    ans = 0
    for c in cells:
        ans += count(c, i)
    print(ans)
