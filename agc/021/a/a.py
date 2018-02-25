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


def solve(N):
    N = str(N)
    ans = 0
    if N == len(N) * '9':
        ans = 9 * len(N)
    elif len(N) == 1:
        ans = int(N)
    elif N[1:] == (len(N)-1) * '9':
        ans = sum(map(int, list(N)))

    elif N[0] == '1':
        ans = 9 * (len(N) - 1)
    else:
        ans = int(N[0]) - 1 + 9 * (len(N)-1)
    return ans

N = input()
print(solve(N))

# assert(solve(100) == 18)
# assert(solve(9995) == 35)
# assert(solve(3141592653589793) == 137)
# assert(solve(1) == 1)
# assert(solve(9) == 9)
# assert(solve(10) == 9)
# assert(solve(18) == 9)
# assert(solve(19) == 10) # corner
# assert(solve(20) == 10)
# assert(solve(25) == 10)
# assert(solve(29) == 11)
# assert(solve(98) == 17)
# assert(solve(99) == 18)
# assert(solve(100) == 18)
# assert(solve(199) == 19)

# def straight(N):
#     N = int(N)
#     ans = 0
#     while N > 0:
#         ans = max(ans, sum(map(int, list(str(N)))))
#         N -= 1
#     return ans

# for i in range(1, 10000):
#     assert(straight(N) == solve(N))
