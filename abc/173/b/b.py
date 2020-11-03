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
d = Counter()
for n in range(N):
    tmp = input()
    d[tmp] += 1
for key in ['AC', 'WA', 'TLE', 'RE']:
    print("{} x {}".format(key, d[key]))

