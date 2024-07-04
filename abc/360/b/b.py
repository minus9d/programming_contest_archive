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


S, T = input().split()

ok = False
for w in range(1, len(S)):
    for c in range(1, w + 1):
        sub = ''.join(S[c-1::w])
        if sub == T:
            ok = True
if ok:
    print('Yes')
else:
    print('No')
