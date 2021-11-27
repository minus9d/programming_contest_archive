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


A, B  = map(int, input().split())
C = A + B

def is_easy(a, b, c):
    a, b, c = [str(x) for x in [a, b, c]]
    if not (max(len(a), len(b)) == len(c)):
        return False
    
    size = max(len(a), len(b))
    format = "{:0" + str(size) + "d}"
    a, b, c = [format.format(int(x)) for x in [a, b, c]]
    # print(format)
    # print(a)
    # print(b)
    # print(c)

    for ch_a, ch_b, ch_c in zip(a, b, c):
        if int(ch_a) + int(ch_b) != int(ch_c):
            return False
    return True


if is_easy(A, B, C):
    print('Easy')
else:
    print('Hard')
