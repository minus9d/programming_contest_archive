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


S = input()

S1 = S.lower()
S2 = S.upper()

d1 = d2 = 0
for c, c1, c2 in zip(S, S1, S2):
  d1 += c != c1
  d2 += c != c2

if d1 < d2:
  print(S1)
else:
  print(S2)
