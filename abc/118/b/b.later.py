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

N, M = map(int, input().split())
s = set()
for n in range(N):
    items = list(map(int, input().split()))
    K = items[0]
    As = items[1:]
    if n == 0:
        s = set(As)
    else:
        s &= set(As)
print(len(s))
