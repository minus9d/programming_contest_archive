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


sys.setrecursionlimit(10 ** 9)


S = input()
S = S[::-1]
S = [int(x) for x in S]

ans = 0
inc = 0
for ch in S:
    ch = (ch + 10 - inc) % 10
    ans += ch + 1
    inc = (inc + ch) % 10

print(ans)
