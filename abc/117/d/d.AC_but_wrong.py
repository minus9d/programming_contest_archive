#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本番中にACしたが、実は嘘解法であることが判明
#
# 本コードのアルゴリズムは以下。
#   Xの上の桁から順に0か1かを多数決で決めていく。
#   ただし、その桁を1にすることでXがKを超えてしまうようなら
#   その桁は0で確定する
# ただし、このコードでは、以下のサンプルで13(X=3)ではなく8(X=4)を
# 出力してしまうため、嘘解法であることが判明
#   3 4
#   4 0 0
# (出展: https://twitter.com/kyuridenamida/status/1092066138706534400)

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


def func(As, x):
    ans = 0
    for a in As:
        ans += a ^ x
    return ans


def add_bit(bits, idx):
    ret = bits[:]
    ret[idx] = 1
    return ret


def arr_to_num(arr):
    num_str = ''.join([str(x) for x in arr])
    return int(num_str, 2)
    

def solve(N, K, As):
    if K == 0:
        return func(As, 0)

    best_x = 0
    IDX_MAX = 42
    idx = IDX_MAX
    bits = [0] * (idx + 1)
    while idx >= 0:
        if arr_to_num(add_bit(bits, IDX_MAX - idx)) > K:
            pass
        else:
            one = 0
            zero = 0
            for a in As:
                if a & (1 << idx): one += 1
                else: zero += 1
            if one >= zero:
                bits[IDX_MAX - idx] = 0
            else:
                bits[IDX_MAX - idx] = 1
        idx -= 1

    best_x = arr_to_num(bits)
    return func(As, best_x)


N, K = map(int, input().split())
As = list(map(int, input().split()))
print(solve(N, K, As))



    



