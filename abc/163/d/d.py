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

MOD = 10 ** 9 + 7

N, K = map(int, input().split())

def sum_1_to_n(n):
    return n * (n + 1) // 2


ans = 0
for k in range(K, N + 2):
    tmp = sum_1_to_n(k - 1)
    start = tmp
    end = N * k - tmp
    # print(start, end)
    ans += end - start + 1
    ans %= MOD
    # print("ans = ", ans)

print(ans)



