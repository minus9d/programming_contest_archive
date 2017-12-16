#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

H, W = map(int, input().split())
N = int(input())
As = list(map(int, input().split()))

ret = []
r = []
for i, a in enumerate(As):
    while a > 0:
        if len(r) == W:
            ret.append(r)
            r = []
        r.append(i + 1)
        a -= 1
ret.append(r)

for i, r in enumerate(ret):
    if i % 2:
        print(*r[::-1])
    else:
        print(*r)

