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

N = int(input())
S = Counter()
for n in range(N):
    s = input()
    if s[0] in 'MARCH':
        S[s[0]] += 1

if len(S) < 3:
    print(0)
else:
    keys = S.keys()
    ans = 0
    for comb in combinations(keys, 3):
        ans += S[comb[0]] * S[comb[1]] * S[comb[2]]
    print(ans)
