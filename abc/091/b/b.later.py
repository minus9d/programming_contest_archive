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

c = Counter()
N = int(input())
for _ in range(N):
    s = input()
    c[s] += 1
M = int(input())
for _ in range(M):
    s = input()
    c[s] -= 1
print(max(list(c.values()) + [0]))

