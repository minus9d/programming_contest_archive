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


N = int(input())
As = list(map(int, input().split()))

P = 0
cells = [0] * 4
for a in As:
    cells[0] = 1
    new_cells = [0] * 4
    for i in range(4):
        j = i + a
        if j > 3:
            P += cells[i]
        else:
            new_cells[j] = cells[i]
    cells = new_cells
print(P)            
