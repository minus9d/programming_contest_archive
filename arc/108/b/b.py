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
s = input()

cnt = 0
t = []
for ch in s:
    t.append(ch)
    if t[-3:] == ['f', 'o', 'x']:
        cnt += 1
        del t[-3:]
print(N - cnt * 3)


