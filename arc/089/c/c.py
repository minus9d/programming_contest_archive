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

def solve():
    N = int(input())
    t, x, y = 0, 0, 0
    for _ in range(N):
        nt, nx, ny = map(int, input().split())
        # print("{} {} {} -> {} {} {}".format(t, x, y, nt, nx, ny))
        dt = nt - t
        if abs(nx - x) + abs(ny - y) > dt or \
           (abs(nx - x) + abs(ny - y) - dt) % 2 == 1:
            return False
        else:
            t, x, y = nt, nx, ny
    return True


if solve():
    print("Yes")
else:
    print("No")

