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


xa, ya = map(int, input().split())
xb, yb = map(int, input().split())
xc, yc = map(int, input().split())

p1 = (xa, ya)
p2 = (xb, yb)
p3 = (xc, yc)

def get_d(p1, p2):
    return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2

d1 = get_d(p1, p2)
d2 = get_d(p1, p3)
d3 = get_d(p2, p3)

ds = sorted([d1, d2, d3])
# print(ds)

if ds[0] + ds[1] == ds[2]:
    print('Yes')
else:
    print('No')
