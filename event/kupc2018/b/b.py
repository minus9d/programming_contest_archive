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

cells = []
for h in range(H):
    cells.append(input())

ini_x = cells[-1].find('s')

for way in product([-1,0,1], repeat=H-1):
    x = ini_x
    y = H - 1
    ok = True
    for w in way:
        x += w
        y -= 1
        if x < 0 or x >= W or cells[y][x] == 'x':
            ok = False
            break
    if ok:
        s = ''
        for w in way:
            if w == -1: s += 'L'
            elif w == 0: s += 'S'
            else: s += 'R'
        print(s)
        sys.exit(0)
print('impossible')
    
    
