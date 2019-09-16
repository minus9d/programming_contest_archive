#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 与えられた文字列の幸福度は、LとRの入れ替わりの数だけで決まることに着目
# 幸福度は、最初の方は2ずつ上げることができる。
# 端数が出る場合は最後に1だけ上げられる

#        change   happiness
# LLLLL  0        4
# LLLRR  1        3 -> 4
# LLRRL  2        2 -> 4
# LLRLR  3        1 -> 3 -> 4


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


def solve(N, K, S):
    prev = S[0]
    change = 0
    for ch in S[1:]:
        change += ch != prev
        prev = ch

    happiness = N - 1 - change

    # K回のうち、use回を使って、幸福度をuse * 2上昇させる
    use = min(K, change // 2)
    happiness += use * 2
    K -= use

    # まだねじれがあれば修正
    if K > 0 and happiness != N - 1:
        happiness += 1

    return happiness


N, K = map(int, input().split())
S = input()
print(solve(N, K, S))

# assert solve(1, 1, "L") == 0
# assert solve(2, 1, "LR") == 1
# assert solve(2, 2, "LR") == 1
# assert solve(2, 2, "LL") == 1
# assert solve(3, 1, "LLL") == 2
# assert solve(3, 1, "LRL") == 2
# assert solve(3, 2, "LRL") == 2
# assert solve(3, 1, "LLR") == 2
