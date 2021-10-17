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


arr = []
S = input()
for i in range(len(S)):
    S = S[1:] + S[0]
    arr.append(S)
arr.sort()
print(arr[0])
print(arr[-1])

