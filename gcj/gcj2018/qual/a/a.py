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

def calc_damage(P):
    damage = 0
    beam = 1
    for ch in P:
        if ch == 'S':
            damage += beam
        else:
            beam *= 2
    return damage
    

def solve():
    D, P = input().split()
    D = int(D)

    if D < P.count('S'):
        return "IMPOSSIBLE"

    swap_num = 0
    while calc_damage(P) > D:
        idx = P.rfind('CS')
        P = P[:idx] + 'SC' + P[idx+2:]
        swap_num += 1
    return swap_num


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    print(solve())
