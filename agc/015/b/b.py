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

S = input()
up = len(S) - 1
down = 0
ans = 0
for ch in S:
    if ch == 'U':
        ans += up * 1 + down * 2
    else:
        ans += up * 2 + down * 1
    down += 1
    up -= 1
print(ans)
