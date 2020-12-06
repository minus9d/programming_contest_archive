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
T = input()

S = '110' * 200000

ans = 0
for i in range(3):
    if S[i:].startswith(T):
        end_pos = 3 * (10 ** 10)
        start_pos = end_pos - len(T)
        while start_pos % 3 != i:
            start_pos -= 1
        # print(i, start_pos)

        tmp = (start_pos - i) // 3 + 1
        ans += max(0, tmp)
print(ans)
