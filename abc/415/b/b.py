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


S = input()
arr = []
for i in range(len(S)):
    if S[i] == '#':
        arr.append(i + 1)
for i in range(len(arr) // 2):
    print(f"{arr[i*2]},{arr[i*2+1]}")

