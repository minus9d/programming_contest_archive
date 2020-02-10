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

def solve_1(N):
    N_str = str(N)
    ans = 0
    for i, ch in enumerate(N_str):
        if i == 0:
            ans += int(ch)
        else:
            ans += 9
    return ans

def solve_2(N):
    N_str = str(N)

    # N = 70543 だとする

    # {1..6}XXXX:
    # XXXXのうち1箇所が1..9のどれか、他はすべて0
    ans = (int(N_str[0]) - 1) * 9 * (len(N_str) - 1)

    # 7XXXX:
    # XXXXの前から順に見ていく
    # ありえるパターンは 7{1..9}000, 70{1..9}00, 700{1..9}0, 7000{1..9}
    # 前から順に考えていく
    # 7{1..9}000 に関しては、1..9のどれも入れない。 +0通り
    # 70{1..9}00 に関しては、1..5のどれかが入れる。 +5通り
    # 700{1..9}0 に関しては、1..9の全部が入れる。この桁よりも前に非0の桁があったため。+9通り
    # 7000{1..9} に関しては、1..9の全部が入れる。 +9通り
    flag = False
    for ch in N_str[1:]:
        if flag:
            ans += 9
        else:
            ans += int(ch)
            if ch != '0':
                flag = True

    # XXXX:
    # 4箇所どこにも1..9の全部が入れる
    for i in range(1, len(N_str) - 1):
        ans += 81 * i

    return ans

def solve_slow_2(n):
    ans = 0
    for i in range(1, n + 1):
        i_str = str(i)
        cnt = 0
        for ch in i_str:
            cnt += ch != '0'
        ans += cnt == 2
    return ans

# for n in range(1, 10000):
#     mine = solve_2(n)
#     gt = solve_slow_2(n)
#     if mine != gt:
#         print("error! n, mine, gt = ", n, mine, gt)
#         sys.exit(0)
#     else:
#         print(n, "ok")


def solve_3(N):
    N_str = str(N)
    size = len(N_str)

    # N = 70543 だとする

    # {1..6}XXXX:
    # XXXXのうち2箇所が1..9のどれか、他はすべて0
    ans = (int(N_str[0]) - 1) * (((size - 1) * (size - 2)) // 2) * 81

    # 7XXXX:
    # "2つだけ非0でXXXXより小さい数"を数えればよい。solve_2を使うと解ける
    if size > 1:
        ans += solve_2(int(N_str[1:]))

    # X:
    # XX:
    # XXX:
    # XXXX:
    # の場合をループで順番に加算
    # 例えばXXXXの場合、
    # 最初の桁は{1..9}, 残り3桁のうちの2つが{1..9}なので
    # 場合の数は9 * 9 * 9 * 3C2
    for size in range(1, len(N_str)):
        ans += 9 * 9 * 9 * (size - 1) * (size - 2) // 2

    return ans

def solve_slow_3(n):
    ans = 0
    for i in range(1, n + 1):
        i_str = str(i)
        cnt = 0
        for ch in i_str:
            cnt += ch != '0'
        ans += cnt == 3
    return ans


# for n in range(1, 10000):
#     mine = solve_3(n)
#     gt = solve_slow_3(n)
#     if mine != gt:
#         print("error! n, mine, gt = ", n, mine, gt)
#         sys.exit(0)
#     else:
#         print(n, "ok")
        

def solve(N, K):
    if K == 1:
        return solve_1(N)
    elif K == 2:
        return solve_2(N)
    else:
        return solve_3(N)


N = int(input())
K = int(input())

print(solve(N, K))

