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

X, Y = map(int, input().split())

def solve(X, Y):
    tmp = Y - 2 * X
    if tmp % 2:
        return False
    b = (Y - 2 * X) // 2

    tmp = 4 * X - Y
    if tmp % 2:
        return False
    a = (4 * X - Y) // 2

    if a >= 0 and b >= 0:
        return True
    else:
        return False

if solve(X, Y):
    print("Yes")
else:
    print("No")



