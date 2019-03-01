#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 終了後に自力AC 
#
# カードを「Aより小さい」「Aに等しい」「Aより大きい」に分ける。
#
# 「Aより小さい」カードで「和がSになる組み合わせの数」は容易に計算できる。
# 「Aより大きい」カードで「和がTになる組み合わせの数」も計算できる。
#
# あとはこれらを組み合わせるだけ

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

N, A = map(int, input().split())
Xs = list(sorted(map(int, input().split())))

lower = []
same = 0
upper = []
for x in Xs:
    if x < A:
        lower.append(A - x)
    elif x == A:
        same += 1
    else:
        upper.append(x - A)

def make_counter(nums):
    counter = Counter({0: 1})
    for n in nums:
        new_counter = Counter()
        for k, v in counter.items():
            # 使う場合、使わない場合それぞれの場合の数を増やす
            new_counter[k] += v
            new_counter[k + n] += v
        counter = new_counter
    return counter

lower_counter = make_counter(lower)
upper_counter = make_counter(upper)

ans = 0
for lk, lv in lower_counter.items():
    # (i) Aに等しい数だけ使う
    if lk == 0:
        # ひとつも選ばれない場合を除くために-1
        ans += 2 ** same - 1
    # (ii) それ以外
    else:
        # Aより小さい数たちと、Aより大きい数たちとの集合の平均がちょうどA
        if lk in upper_counter:
            ans += (2 ** same) * lv * upper_counter[lk]

print(ans)
