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

N = 123
for i in range(1, 10000):
    print(i, end="  ")
    if i <= N and str(i) <= str(N) or i > N and str(i) > str(N):
        print("YES")
    else:
        print("NO")

