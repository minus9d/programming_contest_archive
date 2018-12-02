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

nums = []
for comb in product(['0', '7', '5', '3'], repeat=9):
    candidate = str(int(''.join(comb)))
    if all((x in candidate) for x in ['7', '5', '3']) \
       and '0' not in candidate:
        nums.append(int(candidate))
nums.sort()

ans = 0
for n in nums:
    if n <= N:
        ans += 1
    else:
        break
print(ans)
