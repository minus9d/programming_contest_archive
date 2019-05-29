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
SPs = []
for n in range(N):
    s, p = input().split()
    p = int(p)
    SPs.append((s, -p, n))
SPs.sort()
for s, p, n in SPs:
    print(n + 1)
