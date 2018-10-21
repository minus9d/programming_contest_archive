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
BAs = []
for n in range(N):
    a, b = map(int, input().split())
    BAs.append([b, a])
BAs.sort()
BAs[-1][1] += X

ans = 0
for b, a in BAs:
    ans += b * a
print(ans)
