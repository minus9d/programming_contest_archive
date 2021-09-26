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
As = list(map(int, input().split()))
X = int(input())

sum_a = sum(As)

cnt = (X // sum_a) * N
remain = X - (X // sum_a) * sum_a

for a in As:
    remain -= a
    cnt += 1
    if remain < 0:
        break

print(cnt)

