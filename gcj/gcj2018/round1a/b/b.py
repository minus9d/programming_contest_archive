#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 問題
#   レジがC個ある。i番目のレジは、mi個までの品物を処理できる。
#   処理にかかる時間は、商品の個数がxのとき、mi * si + pi。
#   R個のロボットが、レジを選んでB個の商品を買うとき、
#   所要時間の最小値を求める
# 解法
#   所要時間Tのときに購入が可能かはすぐ調べられるので、二分探索で解ける。
#   本番では、あるレジで購入可能な個数が負になることを許してしまっていたのでWA

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


def faster(R, B, C, Ms, Ss, Ps):
    lo = 0
    hi = int(1e19)

    def check(time):
        buy = []
        for c in range(C):
            cand = (time - Ps[c]) // Ss[c]
            if cand < 0:
                buy.append(0)
            else:
                buy.append(min(Ms[c], cand))
            # 最初は以下のように書いていてWAだった
            # この場合、購入可能な個数が負になってしまう
            # buy.append(min(Ms[c], (time - Ps[c]) // Ss[c]))
        buy.sort(reverse=True)

        # print("time, buy = ", time, buy)
        return sum(buy[:R]) >= B

    while lo < hi:
        k = (lo + hi) // 2
        if check(k):
            hi = k
        else:
            lo = k + 1
    return lo

def solve():
    R, B, C = map(int, input().split())
    Ms = []
    Ss = []
    Ps = []
    for c in range(C):
        m, s, p = map(int, input().split())
        Ms.append(m)
        Ss.append(s)
        Ps.append(p)

    print(faster(R, B, C, Ms, Ss, Ps))

T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
