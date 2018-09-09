#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
from functools import *
import fractions
import heapq 
from itertools import *
import math
import random
import re
import string
import sys

# python3.4では存在しない!!
# from math import gcd

def gcd(a, b):
    if b == 0:
        return a
    else:
        return gcd(b, a % b)

N, X = map(int, input().split())
Xs = map(int, input().split())
diffs = [abs(X - x) for x in Xs]
ans = reduce(gcd, diffs)
print(ans)

