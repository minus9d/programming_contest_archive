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
Vs = list(map(int, input().split()))
Vs.sort()

s = 0
coeff = 1
for i, v in enumerate(Vs):
    if i <= 1:
        s += v
    else:
        coeff *= 2
        s += v * coeff

t = 2 ** (N - 1)

print("{:.15f}".format(s / t))






