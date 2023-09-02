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


N, H, X  = map(int, input().split())
P = list(map(int, input().split()))

for i, p in enumerate(P):
    if H + p >= X:
        print(i + 1)
        break
