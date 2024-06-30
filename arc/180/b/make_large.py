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

N = 500
K = 1
P = [x + 1 for x in range(N)]
P = P[::-1]

print(N, K)
print(*P)
