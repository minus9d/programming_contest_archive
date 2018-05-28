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
    N = 1000
    print(N)
    used = set()

    for n in range(2, N+1):
        m = random.randint(1, n-1)
        print("{} {}".format(n, m))
        used.add((n, m))
        used.add((m, n))

    while True:
        i = random.randint(1, N)
        j = random.randint(1, N)
        if i == j or (i, j) in used:
            continue
        else:
            print("{} {}".format(i, j))
            break
        
    

