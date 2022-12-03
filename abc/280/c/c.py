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
T = input()

ans = None
for i, (s, t) in enumerate(zip(S, T)):
    if s != t:
        ans = i
        break
if ans is None:
    print(len(S) + 1)
else:
    print(ans + 1)
