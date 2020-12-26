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

H, W = map(int, input().split())

mn = 1e9
Ass = []
for h in range(H):
    As = list(map(int, input().split()))
    Ass.append(As)
    mn = min(mn, min(As))

ans = 0
for As in Ass:
    for a in As:
        ans += a - mn
print(ans)
