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


S = input()

prev_one = ''
prev_two = ''

length = len(S)
dp_one = [0] * length
dp_two = [0] * length

for i, ch in enumerate(S):
    if i == 0:
        dp_one[0] = 1
    else:
        prev_one = S[i - 1]
        if prev_one != ch:
            dp_one[i] = max(dp_one[i-1], dp_two[i-1]) + 1
        else:
            dp_one[i] = dp_two[i-1] + 1

    if i >= 2:
        two = S[i - 1] + S[i]
        prev_two = S[i - 3] + S[i - 2]
        if prev_two != two:
            dp_two[i] = max(dp_two[i - 2], dp_one[i - 2]) + 1
        else:
            dp_two[i] = dp_one[i - 2] + 1
    elif i == 1:
        dp_two[i] = 1
    else:
        dp_two[i] = 0

    # print("i = ", i)
    # print("  ", dp_one)
    # print("  ", dp_two)

print(max(dp_one[-1], dp_two[-1]))
        
    
