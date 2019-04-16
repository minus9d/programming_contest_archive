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

N = int(input())
As = []
Bs = []
for n in range(N):
    a, b = map(int, input().split())
    As.append(a)
    Bs.append(b)

def solve(As):
    ret = 1e18
    for a1 in As:
        s = 0
        for a2 in As:
            s += abs(a2 - a1)
        ret = min(ret, s)
    return ret

ans1 = solve(As)
ans2 = solve(Bs)
ans3 = sum(abs(a - b) for a, b in zip(As, Bs))
print(ans1 + ans2 + ans3)


    
