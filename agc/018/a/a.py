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

N, K = map(int, input().split())
As = list(sorted(set(map(int, input().split()))))

def gcd(a, b):
    while b:
    	a, b = b, a % b
    return a

# corner
if len(As) == 1:
    if K == As[0]:
        print("POSSIBLE")
    else:
        print("IMPOSSIBLE")
else:        
    for i in range(len(As)-1):
        diff = As[i+1] - As[i]
        if i == 0:
            unit = diff
        else:
            unit = gcd(unit, diff)
    
    ok = False
    for a in As:
        if (a - K) % unit == 0 and K <= a:
            ok = True
    
    if ok:
        print("POSSIBLE")
    else:
        print("IMPOSSIBLE")
