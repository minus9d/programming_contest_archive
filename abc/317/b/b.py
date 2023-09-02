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


N = int(input())
A = list(map(int, input().split()))
mn = min(A)
mx = max(A)
s = set(A)
for i in range(mn, mx + 1):
    if i not in s:
        print(i)
        break



