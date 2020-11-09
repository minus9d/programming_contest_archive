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

N = input()

n1 = 0
n2 = 0
n0 = 0
cur = 0
for ch in N:
    n = int(ch)
    if n % 3 == 1:
        n1 += 1
        cur += 1
    elif n % 3 == 2:
        n2 += 1
        cur += 2
    else:
        n0 += 1

ans = 0
while (cur % 3) != 0:
    if cur % 3 == 1:
        if n1 > 0:
            ans += 1
            n1 -= 1
            cur -= 1
        elif n2 > 0:
            ans += 1
            n2 -= 1
            cur -= 2
    elif cur % 3 == 2:
        if n2 > 0:
            ans += 1
            n2 -= 1
            cur -= 2
        elif n1 > 0:
            ans += 1
            n1 -= 1
            cur -= 1

if n0 == n1 == n2 == 0:
    print(-1)
else:
    print(ans)
        
            


# if cur % 3 == 0:
#     print(0)
# elif cur % 3 == 1:
#     if n1 > 0:
#         print(1)
#     elif n2 == 2 and n0 == 0:
#         print(-1)
#     else:
#         print(2)
# elif cur % 3 == 2:
#     if n2 > 0:
#         print(1)
#     elif n1 == 2 and n0 == 0:
#         print(-1)
#     else:
#         print(2)

    
