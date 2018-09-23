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

def to_num_list(s):
    seen = {}
    ret = []
    idx = 0
    for ch in s:
        if ch not in seen:
            seen[ch] = idx
            idx += 1
        ret.append(seen[ch])
    return ret

if to_num_list(S) == to_num_list(T):
    print('Yes')
else:
    print('No')
