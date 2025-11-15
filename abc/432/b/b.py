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


A = list(input())
zeros = []
others = []
for ch in A:
    if ch == '0':
        zeros.append(ch)
    else:
        others.append(ch)
others.sort()

ans = [others[0]] + zeros + others[1:]
print(''.join(ans))

