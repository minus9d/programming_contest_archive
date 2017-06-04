#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

N = int(input())

S1 = []
S2 = []
for n in range(N):
    s = int(input())
    if s % 10 == 0:
        S1.append(s)
    else:
        S2.append(s)

if len(S2) == 0:
    print(0)
else:
    ans = sum(S2)
    if ans % 10 == 0:
        S2.sort()
        ans -= S2[0]
    ans += sum(S1)
    print(ans)
