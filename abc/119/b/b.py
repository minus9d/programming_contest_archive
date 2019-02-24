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

ans = 0
N = int(input())
for n in range(N):
    x, u = input().split()
    if u == 'JPY':
        ans += int(x)
    else:
        ans += float(x) * 380000.0
print("{:.9f}".format(ans))


