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
T = input()

slen = len(S)
tlen = len(T)

def can_fill(substr, T):
    for s, t in zip(substr, T):
        if s != '?' and s != t:
            return False
    return True

ans = None
for i in range(len(S) - tlen + 1):
    substr = S[i:i+tlen]
    if can_fill(substr, T):
        S2 = S[:i] + T + S[i+tlen:]
        S2 = S2.replace('?', 'a')
        if ans == None:
            ans = S2
        else:
            ans = min(ans, S2)

if ans is None:
    print('UNRESTORABLE')
else:
    print(ans)



