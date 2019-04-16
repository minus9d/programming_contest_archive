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
XRs = []
for n in range(N):
    XRs.append(tuple(map(int, input().split())))

ans = 0
for x1, r1 in XRs:
    local_ans = 0
    for x2, r2 in XRs:
        diff_x = abs(x2 - x1)
        if r2 - diff_x > 0:
            local_ans += (r2 - diff_x) ** 3
    ans = max(ans, local_ans)
print(ans ** (1.0 / 3))
