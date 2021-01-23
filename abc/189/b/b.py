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

N, X = map(int, input().split())

s = 0
for n in range(N):
    v, p = map(int, input().split())
    s += v * p
    # print("s:", s)
    if s > X * 100:
        print(n + 1)
        sys.exit(0)
print(-1)

