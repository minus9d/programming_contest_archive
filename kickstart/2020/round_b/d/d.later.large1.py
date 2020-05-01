#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
本番中に考えていた方針だとTLEだったのを、
本番後にlogをとってACにしたもの

例として以下の盤面を考える。■は穴。
　　□□□□□□□□
　　□□□□□□□□
　　□□□■■□□□
　　□□□■■□□□
　　□□□■■□□□
　　□□□□□□□□
　　□□□□□□□□

◎で表した部分に到達しさえすれば、あとは確率1.0で右下に到達できる。
　　□□□□□◎□□
　　□□□□□◎□□
　　□□□■■□□□
　　□□□■■□□□
　　□□□■■□□□
　　◎◎◎□□□□□
　　□□□□□□□□

同様に、
△は1/2の確率で、
▽は1/4の確率で、
※は3/4の確率で右下に到達できる点。

　　□□□□※◎□□
　　□□□▽△◎□□
　　□□□■■□□□
　　□□▽■■□□□
　　□※△■■□□□
　　◎◎◎□□□□□
　　□□□□□□□□

というのを左上原点まで延長して考えていった。
きれいに説明できるほど考えが整理できていない
"""

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

def calc_dist(pt1, pt2):
    return abs(pt1[0] - pt2[0]) + abs(pt1[1] - pt2[1])

def func(one_lne, zero_len):
    pass               

def mypow(x, n):
    ans = 1
    while n:
        if n % 2:
            ans *= x
        x *= x
        n >>= 1
    return ans

def solve_fast(W, H, L, U, R, D):
    # ゴールできない場合
    if ((R == W and D == H)
        or (L == 1 and R == W)
        or (U == 1 and D == H)):
        return 0.0

    # 強制的に塗る
    if D == H:
        L = 1
    if R == W:
        U = 1
    

    # (1, 1)からの最も遠い距離
    dist = max(calc_dist((1, 1), (L - 1, D)),
               calc_dist((1, 1), (R, U - 1)))


    # □□□□□★
    # □□□□□★
    # □□□■■
    # □□□■■
    # □□□■■
    #
    # ★の寄与分を考える
    numerator = 0

    numerator_log = 0
    ans = 0

    for h in range(1, U):
        w = R + 1
        if h == 1:
            # choose = 1
            # mul = mypow(2, (dist - (h - 1) - (w - 1) + 1))

            choose_log = 0
            mul_log = (dist - (h - 1) - (w - 1) + 1)

        else:
            # choose *= (w - 2) + (h - 1)
            # choose //= (h - 1)
            # mul //= 2

            choose_log += math.log(((w - 2) + (h - 1)) / (h - 1), 2)
            mul_log -= 1

        # numerator += choose * mul

        ans += math.pow(2.0, (choose_log + mul_log) - (dist + 1))

    # □□□□□
    # □□□□□
    # □□□■■
    # □□□■■
    # □□□■■
    # ★★★
    #
    # ★の寄与分を考える
    for w in range(1, L):
        h = D + 1
        if w == 1:
            # choose = 1
            # mul = mypow(2, (dist - (h - 1) - (w - 1) + 1))

            choose_log = 0
            mul_log = (dist - (h - 1) - (w - 1) + 1)

        else:
            # choose *= (w - 1) + (h - 2)
            # choose //= (w - 1)
            # mul //= 2

            choose_log += math.log(((w - 1) + (h - 2)) / (w - 1), 2)
            mul_log -= 1

        # numerator += choose * mul

        ans += math.pow(2.0, (choose_log + mul_log) - (dist + 1))

    # denominator = 2 ** (dist + 1)
    # gt = numerator / denominator

    # return gt
    return ans


def solve():
    W, H, L, U, R, D = map(int, input().split())
    print("{:.20f}".format(solve_fast(W, H, L, U, R, D)))


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
