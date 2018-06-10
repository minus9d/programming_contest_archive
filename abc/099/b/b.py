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

A, B = map(int, input().split())
diff = B - A
left_idx = diff - 2

talls = []
t = 0
for i in range(999):
    t += (i + 1)
    talls.append(t)

t = talls[left_idx]
print(t - A)

