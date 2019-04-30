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

N, A, B = map(int, input().split())
if B > 0:
    Ds = list(map(int, input().split()))
else:
    Ds = []
Ds.sort()
Ds.append(N + 1)

date = len(Ds) - 1
prev = 0
for d in Ds:
    days = d - prev - 1
    date += days // A
    prev = d
print(N - date)
