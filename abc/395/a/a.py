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
ans = True
for i in range(1, N):
    if A[i] <= A[i-1]:
        ans = False
if ans:
    print('Yes')
else:
    print('No')
