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


A, B = map(int, input().split())

tmp = A / B
c1 = A // B
c2 = c1 + 1
if abs(c1 - tmp) < abs(c2 - tmp):
    print(c1)
else:
    print(c2)


