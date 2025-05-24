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


X, Y  = map(int, input().split())

cnt = 0
for i in range(1, 7):
    for j in range(1, 7):
        cnt += i + j >= X or abs(i - j) >= Y

print(f"{cnt / 36:.11f}")


