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

N, S, D = map(int, input().split())

ok = False
for n in range(N):
    x, y = map(int, input().split())
    if x < S and y > D:
        ok = True
if ok:
    print('Yes')
else:
    print('No')
