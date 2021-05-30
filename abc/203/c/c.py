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

N, K = map(int, input().split())

pos = 0
money = K

ABs = []
for n in range(N):
    a, b = map(int, input().split())
    ABs.append((a, b))
ABs.sort()

i = 0

while i < N:
    a, b = ABs[i]
    if pos + money >= a:
        money -= a - pos
        pos = a
        money += b
        i += 1

        if i == N:
            break
    else:
        break
            

if money:
    pos += money

print(pos)


    

