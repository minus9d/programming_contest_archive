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


def solve(T):
    # 先頭が 10101010 だったらずっとそれを続ける
    i = 0
    ans = 0
    while T[i:i+2] == "10":
        ans += len(T) - i
        i += 2

    return ans + solve2(T[i:])
        

def solve2(T):
    size = len(T)
    num1 = T.count("1")
    num0 = size - num1

    # 1だけ並べる
    half = num1 // 2
    ans = half * (half + 1)
    if num1 % 2 == 1:
        ans += (num1 // 2) + 1

    # この時点で奇数番目、偶数番目にいる1の数
    # print("num1:", num1)
    even1 = num1 // 2
    odd1 = num1 - even1
    # print("  even1, odd1 = ", even1, odd1)

    # 反転するぶん
    even_rev = 0
    odd_rev = 0

    # 0を後ろから入れていく
    last_idx = size - 1
    for _ in range(num0):
        zero_idx = T.rfind("0", 0, last_idx + 1)
        last_idx = zero_idx
        # 後ろにずれる要素の数は？
        insert_num = size - zero_idx - 1

        # 反転させる
        if insert_num % 2:
            even_rev, odd_rev = odd_rev, even_rev

        # insert_numの分を
        if insert_num % 2 == 0:
            even1 -= insert_num // 2
            odd1 -= insert_num // 2
            even_rev += insert_num // 2
            odd_rev += insert_num // 2
        else:
            mn = insert_num // 2
            mx = mn + 1
            if even1 == odd1:
                even1 -= mx
                odd1 -= mn
                even_rev += mn
                odd_rev += mx
            else:
                # odd1 > even1
                odd1 -= mx
                even1 -= mn
                odd_rev += mn
                even_rev += mx

        ans += odd1 + odd_rev
        # print("even1, odd1, even_rev, odd_rev = ", even1, odd1, even_rev, odd_rev)


    return ans
        



def main():
    T = input()
    print(solve(T))


main()
