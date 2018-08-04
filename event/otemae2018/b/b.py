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

_, M = map(int, input().split())
s = 0
cnt = 0
for a in sorted(list(map(int, input().split())), reverse=True):
    s += a
    cnt += 1
    if s >= M:
        break
print(cnt)
