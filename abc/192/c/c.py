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

N, K = map(int, input().split())

p = N
for k in range(K):
    p = str(p)
    g1 = sorted(list(p), reverse=True)
    g2 = g1[::-1]
    f = int(''.join(g1)) - int(''.join(g2))
    p = f
print(p)
