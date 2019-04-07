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
    N = input()
    a = b = ''
    for ch in N:
        if ch == '4':
            a += '2'
            b += '2'
        else:
            a += ch
            b += '0'
    print(int(a), int(b))


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
