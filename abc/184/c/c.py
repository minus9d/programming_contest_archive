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

r1, c1 = map(int, input().split())
r2, c2 = map(int, input().split())

def solve(r1, c1, r2, c2):
    if r1 == r2 and c1 == c2:
        return 0
    if r1 + c1 == r2 + c2 or r1 - c1 == r2 - c2:
        return 1
    if abs(r1 - r2) + abs(c1 - c2) <= 3:
        return 1

    if ((r1 + c1) % 2) == ((r2 + c2) % 2):
        return 2

    diff1 = abs(r1 - r2)
    diff2 = abs(c1 - c2)
    diff = abs(diff1 - diff2)
    if diff <= 3:
        return 2

    return 3


print(solve(r1, c1, r2, c2))

