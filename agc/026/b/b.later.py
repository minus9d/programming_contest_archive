#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
# 本番中には解けなかった。解説pdfにある3つの場合分けはできた。
# B個の購入を可能なかぎりしたあとの個数が、「Cより大きくBより小さい」値に
# なることがあるとNoになる、ということには気づいたのだが、
# どう解いてよいか混乱して手がつけられなかった
#
#
# 解説pdf https://img.atcoder.jp/agc026/editorial.pdf を見た
#
# B個の購入を行った直後の個数の遷移を、mod Bの世界で考える。
#   最初は A mod B個。
#   B個の購入を可能な限り行った後も A mod B個で変わらず。
#   D個入荷すると    (A + D) mod B個。
# つまり、入荷するたびに、
# A からスタートして (A + D) mod B, (A + 2D) mod B, ... と遷移していく。
# 
# 遷移を無限に繰り返すと、mod Bの世界でのとりうる値は、g = gcd(B, D)として
#   (A % g), g + (A % g), 2g + (A % g), ..., kg + (A % g) (kは、kg + (A % g)がB未満となる最大の整数) のどれかとなる。
# ここでkを直接求めるのは難しい。
# かわりに、mを整数として、mg + (A % g)が最初にB以上となるのを求めるのは簡単で、それは B + (A % g)。
# これよりひとつ分小さいのは、B + (A % g) - gで、これが kg + (A % g)に等しい。
# 
# (A % g) + B - g が、C を超える場合、次に入荷が行われない。次もBを引くと個数が負になってしまうので No。
# (A % g) + B - g が、C 以下の場合、次に入荷が行われる。Yes。
#
#
# 解説PDFの、「また，(B/g − 1) × inv(D/g, B/g) 回 D を足したときにこの上界が達成できます」
# については理解できていない。
#



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


def gcd(a, b):
    while b:
        a, b = b, a % b
    return a


def solve(A, B, C, D):
    if B > A:
        return "No"
    if B > D:
        return "No"
    if B <= C:
        return "Yes"

    g = gcd(B, D)
    if B - g + (A % g) > C:
        return "No"
    else:
        return "Yes"


T = int(input())
for t in range(T):
    A, B, C, D = map(int, input().split())
    print(solve(A, B, C, D))
    

