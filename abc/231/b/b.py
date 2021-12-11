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
cnt = Counter()
for n in range(N):
    s = input()
    cnt[s] += 1
print(cnt.most_common()[0][0])
