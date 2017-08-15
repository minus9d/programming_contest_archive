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

# N = 100000
# a = list(range(N+1))
# a[56789] = 33333
# print(N)
# print(*a)

import random
N = random.randint(1,100000)
a = list(range(N+1))
i1,i2 = random.sample(a,2)
a[i1] = i2
print(N)
print(*a)

