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

N, Y = map(int, input().split())
Y2 = Y // 1000

for a in range(2001):
    for b in range(2001 - a):
        if 9 * a + 4 * b + N == Y2 and a + b <= N:
            print(a, b, N - a - b)
            sys.exit(0)
print(-1, -1, -1)
