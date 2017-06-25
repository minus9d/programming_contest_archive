#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

MOD = 1000000007
def func(n):
    ret = 1
    for i in range(n):
        ret *= (i + 1)
        ret %= MOD
    return ret

N, M = map(int, input().split())
if N == M:
    print((2 * func(N)**2) % MOD)
elif abs(N - M) == 1:
    print((func(N) * func(M)) % MOD)
else:
    print(0)
