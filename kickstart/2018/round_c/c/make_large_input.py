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

T = 100
print(T)
for t in range(T):
    x1 = random.randint(1, 100000)
    y1 = random.randint(1, 100000)
    C = random.randint(1, 100000)
    D = random.randint(1, 100000)
    E1 = random.randint(1, 100000)
    E2 = random.randint(1, 100000)
    F= random.randint(1, 100000)
    N = random.randint(999900, 1000000)
    K = random.randint(9990, 10000)
    print(N, K, x1, y1, C, D, E1, E2, F)

