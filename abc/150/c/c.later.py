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

N = int(input())
P = tuple(map(int, input().split()))
Q = tuple(map(int, input().split()))

shff = list(range(1, N + 1))
idx1 = -1
idx2 = -1
for i, perm in enumerate(permutations(shff)):
    if perm == P:
        idx1 = i
    if perm == Q:
        idx2 = i
print(abs(idx1 - idx2))


