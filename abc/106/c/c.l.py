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


def solve(S, K):
    if min(S) == max(S) == '1':
        return 1
    else:
        for i in range(len(S)):
            if S[i] != '1':
                if K <= i:
                    return 1
                else:
                    return int(S[i])

S = input()
K = int(input())
print(solve(S, K))                

# assert solve('111', 1) == 1
# assert solve('111', 2) == 1
# assert solve('111', 3) == 1

# assert solve('12', 1) == 1
# assert solve('12', 2) == 2
# assert solve('12', 100) == 2

# assert solve('21', 1) == 2
# assert solve('21', 2) == 2
# assert solve('21', 100) == 2

# assert solve('121', 1) == 1
# assert solve('121', 2) == 2
# assert solve('121', 3) == 2
# assert solve('121', 100) == 2

# assert solve('1121', 1) == 1
# assert solve('1121', 2) == 1
# assert solve('1121', 3) == 2
# assert solve('1121', 100) == 2
