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


sys.setrecursionlimit(10 ** 9)


def solve1():

    N = 1000
    
    UV = []
    for i in range(N-1):
        for j in range(i + 1, N):
            UV.append((i, j))
    
    M = len(UV)
    
    print(N, M)
    for u, v in UV:
        print(u + 1, v + 1)
    
    for i in range(N):
        if random.randint(0, 100):
            print('D', end='')
        else:
            print('S', end='')
    print()


def solve2():

    N = 100000
    M = 99999
    
    UV = []
    for i in range(N-1):
        UV.append((i, i+1))
    
    M = len(UV)
    
    print(N, M)
    for u, v in UV:
        print(u + 1, v + 1)
    
    for i in range(N):
        if i < 50000:
            print('D', end='')
        else:
            print('S', end='')
    print()


def solve3():

    N = 10
    M = 9
    
    UV = []
    for i in range(N-1):
        UV.append((i, i+1))
    
    M = len(UV)
    
    print(N, M)
    for u, v in UV:
        print(u + 1, v + 1)
    
    for i in range(N):
        if i < N // 2:
            print('D', end='')
        else:
            print('S', end='')
    print()


solve3()

