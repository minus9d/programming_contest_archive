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


N, X  = map(int, input().split())
As = list(map(int, input().split()))
As = [a - 1 for a in As]

X -= 1
arr = [0] * N
while True:
    if arr[X]:
        break
    arr[X] = 1
    X = As[X]
print(sum(arr))

