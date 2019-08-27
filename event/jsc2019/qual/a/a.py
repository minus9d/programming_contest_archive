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

M, D = map(int, input().split())

ans = 0
for m in range(1, M + 1):
    for d in range(1, D + 1):
        d1 = d // 10
        d2 = d % 10
        if m == d1 * d2 and d1 >= 2 and d2 >= 2:
            ans += 1

print(ans)

