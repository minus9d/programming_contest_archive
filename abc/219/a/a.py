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


sys.setrecursionlimit(10 ** 9)


X = int(input())
nums = [40, 70, 90]
for n in nums:
    if X < n:
        print(n - X)
        sys.exit(0)
print('expert')

