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


S, T, X  = map(int, input().split())

ans = None
n = S
while True:
    if n == X:
        ans = True
        break

    n += 1
    if n == 24:
        n = 0
    if n == T:
        break

if ans:
    print('Yes')
else:
    print('No')
