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
ans = 0
for n in range(1, N + 1):
    s1 = str(n)
    s2 = oct(n)[2:]
    if '7' not in s1 and '7' not in s2:
        ans += 1
print(ans)


