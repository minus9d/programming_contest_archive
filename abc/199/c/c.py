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

N = int(input())
S = list(input())
Q = int(input())

def flip(idx):
    if idx < N:
        return idx + N
    else:
        return idx - N


flipped = False
for q in range(Q):
    t, a, b = map(int, input().split())
    a -= 1
    b -= 1
    if t == 1:
        if flipped:
            a = flip(a)
            b = flip(b)
        S[a], S[b] = S[b], S[a]
    else:
        flipped = not flipped

if flipped:
    S = S[N:] + S[:N]

print(''.join(S))

            
