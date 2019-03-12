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

X = int(input())

s = set()
s.add(1)
for i in range(2, 1001):
    t = i
    while True:
        t *= i
        if t > 1000:
            break
        s.add(t)

while True:
    if X in s:
        print(X)
        break
    else:
        X -= 1
