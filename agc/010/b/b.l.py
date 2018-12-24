#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
解説PDFの英語版に従い実装
"""

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
A = list(map(int, input().split()))

A_sum = sum(A)
removed_unit = N * (N + 1) // 2

if A_sum % removed_unit:
    print('NO')
else:
    k = A_sum / removed_unit
    for i in range(N):
        d = A[(i + 1) % N] - A[i]
        if k - d >= 0 and (k - d) % N == 0:
            pass
        else:
            print('NO')
            sys.exit(0)
    print('YES')
