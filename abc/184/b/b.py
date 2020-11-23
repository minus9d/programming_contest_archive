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

N, X = map(int, input().split())
S = input()
for ch in S:
    if ch == 'o':
        X += 1
    else:
        X -= 1
        if X < 0: X = 0
print(X)


