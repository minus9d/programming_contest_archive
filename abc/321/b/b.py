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


N, X  = map(int, input().split())
A = list(map(int, input().split()))

for i in range(101):
    B = A + [i]
    B.sort()
    result = sum(B[1:N-1])
    if result >= X:
        # print("res = ", result, B)
        print(i)
        sys.exit(0)
print(-1)


