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

A, B = map(int, input().split())

mx = max(A, B)
mn = min(A, B)

arr1 = list(range(1, mx + 1))

arr2 = arr1[:mn]
j = 0
for i in range(mn, mx):
    arr2[j] += arr1[i]
    j += 1
    if j == mn:
        j = 0

if A >= B:
    ans = arr1 + [-x for x in arr2]
else:
    ans = arr2 + [-x for x in arr1]
print(*ans)



