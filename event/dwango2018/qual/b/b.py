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

S = input()
def solve(S):
    stack = []
    ans = 0
    for ch in S:
        if ch == '2':
            stack.append(ch)
            ans = max(ans, len(stack))
        else:
            if len(stack) == 0:
                return -1
            else:
                stack = stack[:-1]
    if len(stack) != 0:
        return -1
    else:
        return ans

print(solve(S))
