#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
本番ではsmallのみAC、
本番中に考えていた方針はTLEだが本番後にlogをとってAC

ここでは、はてなブログに載せた解説
https://minus9d.hatenablog.com/entry/2020/05/01/182724
の方法で解く
"""

import math


# log2(n!)のテーブルを作成
log_table = [0] * 200001
log_value = 0
for i in range(1, 200001):
    log_value += math.log(i, 2)
    log_table[i] = log_value


def log_of_choose(n, k):
    """log C(n, k)を求める"""
    return log_table[n] - log_table[k] - log_table[n - k]


def calc_probability(x, y):
    """(1, 1)から(x, y)に到着する確率を求める
    """
    x -= 1
    y -= 1
    return log_of_choose(x + y, x) - (x + y)


def solve_fast(W, H, L, U, R, D):

    ans = 0.0

    # ◎の部分を下から順に
    # □□□□□◎
    # □□□□◎
    # □□□■□
    # □□□■□
    # □□□□□
    if R != W:
        x = R + 1
        y = U - 1
        while y >= 1:
            log2_of_prob = calc_probability(x, y)
            ans += pow(2, log2_of_prob)
            x += 1
            y -= 1

    # ◎の部分を右から順に
    # □□□□□
    # □□□□□
    # □□□■□
    # □□□■□
    # □□◎□□
    # 　◎
    # ◎
    if D != H:
        x = L - 1
        y = D + 1
        while x >= 1:
            log2_of_prob = calc_probability(x, y)
            ans += pow(2, log2_of_prob)
            x -= 1
            y += 1

    return ans


def solve():
    W, H, L, U, R, D = map(int, input().split())
    print("{:.20f}".format(solve_fast(W, H, L, U, R, D)))


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
