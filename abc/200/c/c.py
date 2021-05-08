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

N = int(input())
As = list(map(int, input().split()))

d = Counter()
for a in As:
    d[a % 200] += 1

ans = 0
for k, v in d.items():
    ans += v * (v - 1) // 2
print(ans)


