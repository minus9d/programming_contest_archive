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

c = Counter()
N, K = map(int, input().split())
for k in range(K):
    d = int(input())
    As = list(map(int, input().split()))
    for a in As: c[a] += 1
print(N - len(c))


