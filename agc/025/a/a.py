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

def get_sum(n):
    n_str = str(n)
    ret = 0
    for ch in n_str:
        ret += int(ch)
    return ret

A = 1
B = N - A
ans = 1e10
while B >= 1:
    ans = min(ans, get_sum(A) + get_sum(B))
    A += 1
    B -= 1
print(ans)

