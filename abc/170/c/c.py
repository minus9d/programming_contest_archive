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

X, N = map(int, input().split())
Ps = list(map(int, input().split()))
P_set = set(Ps)

ans = 1e9
for i in range(-105, 105):
    if i in P_set:
        continue
    if abs(ans - X) > abs(i - X):
        ans = i
print(ans)


