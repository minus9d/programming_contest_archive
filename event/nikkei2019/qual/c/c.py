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

def solve(N, ABs):
    Cs = []
    for n in range(N):
        a, b = ABs[n]
        Cs.append((a + b, a, b))
    Cs.sort()
    Cs.reverse()
    
    taka = 0
    aoki = 0
    for i, c in enumerate(Cs):
        if i % 2 == 0:
            taka += Cs[i][1]
        else:
            aoki += Cs[i][2]
    return taka - aoki

def main():
    N = int(input())
    ABs = []
    for n in range(N):
        a, b = map(int, input().split())
        ABs.append((a, b))
    print(solve(N, ABs))
main()

# def testcase(N, ABs, expected):
#     mine = solve(N, ABs)
#     if mine != expected:
#         print("error!")
#         print("  N = ", N)
#         print("  ABs = ", ABs)
#         print("  expected = ", expected)
#         print("  mine = ", mine)

# testcase(3, [(10,10),(20,20),(30,30)], 20)
# testcase(3, [(20,10),(20,20),(20,30)], 20)
# testcase(6, [(1,1000000000)]*6, -2999999997)
# testcase(3, [(10,1000),(10,10),(30,30)], 20 - 30)
# testcase(4, [(10,1000),(10,10),(30,30)], 20 - 30)

