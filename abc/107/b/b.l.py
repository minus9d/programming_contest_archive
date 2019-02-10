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
    s = input()
    if s != '.' * W:
        cells.append(s)

new_cells = [''] * len(cells)
for w in range(W):
    delete = True
    for c in cells:
        if c[w] == '#':
            delete = False
    if not delete:
        for h, c in enumerate(cells):
            new_cells[h] += cells[h][w]

for c in new_cells:
    print(c)
