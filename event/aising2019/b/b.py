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

N = int(input())
A, B = map(int, input().split())
Ps = list(map(int, input().split()))

c1 = 0
c2 = 0
c3 = 0
for p in Ps:
    if p <= A: c1 += 1
    elif p <= B: c2 += 1
    else: c3 += 1
print(min(c1, c2, c3))

    
