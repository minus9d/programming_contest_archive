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
Ps = list(map(int, input().split()))

Ps = [None, None] + Ps

ans = 0
idx = N

while idx != 1:
    idx = Ps[idx]
    ans += 1

print(ans)
