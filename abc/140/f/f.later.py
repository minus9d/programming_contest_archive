#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 参考: https://atcoder.jp/contests/abc140/submissions/7402925
# できるだけ大きいスライムを貪欲に生んでいく
# 自力コードはTLEのためmaspyさんのコードを参考にした

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


def solve(N, S):
    S = sorted(S)
    used = [S[-1]]
    unused = S[:-1]
    for _ in range(N):
        next_used = []
        next_unused = []
        for p in used[::-1]:
            while unused:
                x = unused.pop()
                if x < p:
                    next_used.append(x)
                    break
                else:
                    next_unused.append(x)
                    continue
        used += next_used
        used.sort()
        unused = unused + next_unused[::-1]
    
    return len(used) == (2**N)


N = int(input())
S = list(map(int, input().split()))
print("Yes" if solve(N, S) else "No")
