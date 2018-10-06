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

N, T = map(int, input().split())
ans = 1e9
for n in range(N):
    c, t = map(int, input().split())
    if t <= T:
        ans = min(ans, c)
if ans == 1e9:
    print('TLE')
else:
    print(ans)

