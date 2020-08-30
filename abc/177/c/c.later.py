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

N = int(input())
As = list(map(int, input().split()))

MOD = 10**9 + 7
ans = 0
s = 0
i = N - 1
for n in range(N - 2, -1, -1):
    s += As[i]
    s %= MOD
    i -= 1
    ans += s * As[n]
    ans %= MOD

print(ans)
    
