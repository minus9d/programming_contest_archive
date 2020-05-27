#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
パンケーキが価値があるのは、ちょうど等分で割り切れるとき。
すべてのパンケーキについて、1等分 .. D等分を試して
(スライスのサイズ, 何個のスライスが取れるか) のタプルを得る

Python 3だとTLE
"""

from __future__ import print_function
from __future__ import division

import array
from bisect import *
from collections import *
import fractions
from fractions import Fraction
import heapq
from itertools import *
import math
import random
import re
import string
import sys

# Python 2, 3両対応
if sys.version_info[0] == 2:
    input = raw_input
    gcd = fractions.gcd
elif sys.version_info[0] == 3:
    gcd = math.gcd


class MyFraction:
    """fractions.Fractionがあまりに遅いので自分で実装"""
    def __init__(self, n, d):
        gcd_value = gcd(n, d)
        self.numerator = n // gcd_value
        self.denominator = d // gcd_value
        self.real = n / d

    # hashのkeyとして使うために__hash__, __eq__が必要

    def __hash__(self):
        hashed_value = hash((self.numerator, self.denominator))
        return hash((self.numerator, self.denominator))

    def __eq__(self, other):
        return (self.numerator, self.denominator) == \
        (other.numerator, other.denominator)

    def __repr__(self):
        return "{} / {} ({})".format(self.numerator, self.denominator, self.real)


def mydiv(n, fraction):
    """floor(n(整数) / fraction)を返す"""
    return (n * fraction.denominator // fraction.numerator)


def solve_set3(N, D, As):
    ans = 10 ** 10
    slice_size_to_slice_num_list = defaultdict(list)
    for a in As:
        for d in range(1, D + 1):

            # fractions.Fraction()は非常に遅い
            # slice_size = Fraction(a, d)

            # そのため、自作クラスを使う
            slice_size = MyFraction(a, d)

            slice_num = d
            slice_size_to_slice_num_list[slice_size].append(slice_num)

    # slice_sizeのうち、D個カットできる境目を二分探索する
    # これにより、後段でO(N)でスライスが可能かをチェックする必要がなくなる
    slice_size_list = list(slice_size_to_slice_num_list.keys())
    slice_size_list.sort(key=lambda obj: obj.real)
    lo = 0
    hi = len(slice_size_list)
    while hi - lo > 1:
        mid = (lo + hi) // 2

        # パンケーキからslice_sizeサイズのスライスを何個作れるか？
        slice_size = slice_size_list[mid]
        cuttable_slice_num = 0
        for a in As:
            cuttable_slice_num += mydiv(a, slice_size)
            if cuttable_slice_num >= D:
                break

        if cuttable_slice_num >= D:
            lo = mid
        else:
            hi = mid

    # カット可能なスライスの範囲のみを探索
    for slice_size in slice_size_list[:(lo + 1)]:
        slice_num_list = slice_size_to_slice_num_list[slice_size]

        # スライスの個数が小さいものから順番に
        slice_num_list.sort()
        cnt = 0
        profit = 0
        for slice_num in slice_num_list:
            cnt += slice_num
            if cnt <= D:
                profit += 1

        ans = min(ans, D - profit)

    return ans         


def solve():
    N, D = map(int, input().split())
    As = list(map(int, input().split()))
    print(solve_set3(N, D, As))


def main():
    T = int(input())
    for testcase in range(T):
        print("Case #{}: ".format(testcase+1), end="")
        solve()


main()