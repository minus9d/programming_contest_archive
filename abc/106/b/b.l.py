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
ans = 0
for i in range(1, N + 1, 2):
    n = 0
    for j in range(1, i + 1):
        n += (i % j == 0)
    if n == 8:
        ans += 1
print(ans)
