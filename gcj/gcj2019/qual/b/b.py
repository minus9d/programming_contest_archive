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
    N = int(input())
    P = input()
    if P[0] == 'S' and P[-1] == 'E':
        ret = 'E' * (N - 1) + 'S' * (N - 1)
    elif P[0] == 'E' and P[-1] == 'S':
        ret = 'S' * (N - 1) + 'E' * (N - 1)
    elif P[0] == P[-1] == 'S':
        x = 0
        for i in range(len(P)):
            p = P[i]
            if p == 'E':
                x += 1
                if P[i + 1] == 'E':
                    break
        ret = 'E' * x + 'S' * (N - 1) + 'E' * (N - 1 - x)
    else:  # P[0] == P[-1] == 'E':
        y = 0
        for i in range(len(P)):
            p = P[i]
            if p == 'S':
                y += 1
                if P[i + 1] == 'S':
                    break
        ret = 'S' * y + 'E' * (N - 1) + 'S' * (N - 1 - y)

    print(ret)


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
