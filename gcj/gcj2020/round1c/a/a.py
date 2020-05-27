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


def solve():
    X, Y, path = input().split()
    X, Y = [int(x) for x in (X, Y)]

    d = 0
    for ch in path:
        if ch == 'N':
            Y += 1
        elif ch == 'S':
            Y -= 1
        elif ch == 'E':
            X += 1
        elif ch == 'W':
            X -= 1
        d += 1
        if d >= abs(X) + abs(Y):
            print(d)
            return
    print("IMPOSSIBLE")


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
