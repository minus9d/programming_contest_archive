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


def solve():
    N = int(input())
    Hs = list(map(int, input().split()))
    ans = 0
    for n in range(1, N - 1):
        ans += Hs[n] > Hs[n - 1] and Hs[n] > Hs[n + 1]
    print(ans)


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
