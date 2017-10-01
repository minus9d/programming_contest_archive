#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

N = int(input())

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def solve(N):
    for a in range(1, 3501):
        N1 = 4*a - N
        N2 = N * a
        if N1 < 0: continue
        for b in range(1, 3501):
            N3 = b * N1 - N2
            N4 = b * N2
            if N4 > 0 and N3 > 0 and N4 % N3 == 0:
                print(a, b, N4//N3)
                return
    
solve(N)

