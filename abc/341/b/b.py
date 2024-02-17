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


N = int(input())
As = list(map(int, input().split()))
for n in range(N-1):
    # print(As)
    a = As[n]
    s, t = map(int, input().split())
    times = a // s
    As[n + 1] += times * t
    As[n] -= times * s
    # print(As)
    # print("---")
print(As[-1])
    

