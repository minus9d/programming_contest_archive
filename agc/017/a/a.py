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

N, P = map(int, input().split())
As = list(map(int, input().split()))
odd = sum(1 for x in As if x % 2 == 1)
even = N - odd

def C(n, k):
    ans = 1
    for i in range(n - k + 1, n + 1):
        ans *= i
    for j in range(1, k + 1):
        ans //= j
    return ans

even_way = 0
for i in range(even + 1):
    even_way += C(even, i)

ans = 0
if P == 0:
    for j in range(0, odd + 1, 2):
        ans += C(odd, j)
else:
    for j in range(1, odd + 1, 2):
        ans += C(odd, j)
ans *= even_way
print(ans)

    
