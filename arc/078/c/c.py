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
As = list(map(int, input().split()))

s1 = 0
s2 = sum(As)

ans = 1e15
for i in range(N-1):
    s1 += As[i]
    s2 -= As[i]
    ans = min(ans, abs(s1 - s2))
print(ans)
