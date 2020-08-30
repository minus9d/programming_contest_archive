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
T = input()

ans = 1e9
i = 0
while True:
    S2 = S[i:i+len(T)]
    if len(S2) != len(T):
        break
    i += 1

    tmp = 0
    for s, t in zip(S2, T):
        tmp += s != t
    ans = min(ans, tmp)

print(ans)
    
