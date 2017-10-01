#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 動画解説を見る
#
# 110101以下の数は、以下のいずれかである
#
# 110101
# 110100 (1を一つ選んで0にする、それ以下の桁はなんでもよいので?とする)
# 1100??
# 10????
# 0?????
#
# 上の各パターンについて条件を満たすものをそれぞれ探し、maxをとる
# 各パターンでは、0になるべき桁が必ず0になるようにする
#
# 実装上は、?をすべて1で置換。orをとった結果、0の箇所に1が来ないようにする
#
# 110101
# 110011
# 101111
# 011111



import array
from bisect import *
from collections import *
import fractions
import heapq
from itertools import *
import math
import re
import string

N, K = map(int, input().split())
A = []
B = []
for n in range(N):
    a, b = map(int, input().split())
    A.append(a)
    B.append(b)

ret = 0

# orをとって 110101 以下になるもののみretに足す
for n in range(N):
    if K | A[n] == K:
        ret += B[n]

# Kの下位ビットから順に見ていき、もし1があれば、その桁を0にして、その桁より下位をすべて1にする
for i in range(31):
    # n番目の桁が0なら、1にする
    if (K >> i) & 1 == 0:
        K |= (1 << i)
    else:
        # n番目の桁が1なら、0にする
        K ^= (1 << i)

        local_ret = 0
        for n in range(N):
            if K | A[n] == K:
                local_ret += B[n]
        ret = max(ret, local_ret)

        # また1に戻す
        K |= (1 << i)


print(ret)
