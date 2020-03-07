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

As = []
for _ in range(3):
    As.append(list(map(int, input().split())))
N = int(input())

s = set()
for n in range(N):
    b = int(input())
    s.add(b)

table = [[0] * 3 for _ in range(3)]
for h in range(3):
    for w in range(3):
        a = As[h][w]
        table[h][w] = (a in s)

# for t in table:
#     print(t)

ans = False
for h in range(3):
    if table[h][0] == table[h][1] == table[h][2] == True: ans = True
for w in range(3):
    if table[0][w] == table[1][w] == table[2][w] == True: ans = True
if table[0][0] == table[1][1] == table[2][2] == True: ans = True
if table[0][2] == table[1][1] == table[2][0] == True: ans = True

if ans:
    print("Yes")
else:
    print("No")


