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
S = input()
c = Counter(S)
ans = 1
for v in c.values():
    ans *= (v + 1)
print((ans - 1) % 1000000007)
