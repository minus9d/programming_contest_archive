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

A, B, C = map(int, input().split())
for n in range(A, B + 1):
    if n % C == 0:
        print(n)
        sys.exit(0)
print(-1)
