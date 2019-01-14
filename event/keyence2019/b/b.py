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


def solve(S):
    remove = len(S) - 7
    if remove == 0:
        return S == 'keyence'
    for i in range(len(S) - remove + 1):
        T = S[:i] + S[i+remove:]
        if T == 'keyence':
            return True
    return False
    
if solve(S):
    print('YES')
else:
    print('NO')
