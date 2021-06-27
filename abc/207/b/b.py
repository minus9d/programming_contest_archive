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


A, B, C, D  = map(int, input().split())
t1 = C * D - B
if t1 <= 0:
    print(-1)
else:
    ans = (A + t1 - 1) // t1
    print(ans)


