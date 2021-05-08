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

def simulate(N):
    arr = []
    for i in range(1, N + 1):
        for j in range(1, N + 1):
            for k in range(1, N + 1):
                arr.append((i, j, k))
    print(arr)

    arr.sort(key=lambda x: (x[0] + x[1] + x[2],
                            x[0],
                            x[1]))

    print("=" * 40)
    for i, a in enumerate(arr):
        print(i, a, sum(a), a[0], a[1])
    print()
    counter = Counter()
    for a in arr:
        counter[sum(a)] += 1
    for k, v in sorted(counter .items()):
        print(k, v)
        
# for n in range(1, 10):
#     simulate(n)
#     print()

def get_comb(N, s):
    m = N - 1
    naive = m * (m - 1) // 2

    


def get_arr(N):
    arr = []
    for k in range(N):
        arr.append((k + 1) * (k + 2) // 2)
    for k in range(N, 2 * N):
        arr.append((9 * N \
                    - 3 * N ** 2 \
                    + 6 * k * N \
                    - 6 * k - 2 * k ** 2 - 4) // 2)
    for k in range(2 * N, 3 * N - 2):
        arr.append((3 * N - k - 1) * (3 * N - k - 2) // 2)
    return arr
    # print(arr)


# for n in range(1, 10):
#     print(get_arr(n))
#     print()

def solve(N, K):

    # N = 5のとき
    # (1 + x + x^2 + x^3 + x^4) ^ 3
    # の係数を考える

    # see https://oeis.org/A109439
    arr = get_arr(N)

    so_far = 0
    for k, v in enumerate(arr):
        k += 3
        so_far += v
        if so_far >= K:
            # 数値の合計がkで、かつ、順番がm番目の数を探していく
            m = K - (so_far - v)
            # print("k, so_far, v, m = ", k, so_far, v, m)

            # 綺麗さが1, 2, ..., Nでループ
            so_far2 = 0
            for clean in range(1, N + 1):
                # 美味しさ+人気度
                yum_pop = k - clean
                # print("clean, yum_pop = ", clean, yum_pop)
                if not (2 <= yum_pop <= N * 2):
                    continue
                yum_min = max(1, yum_pop - N)
                yum_max = yum_pop - yum_min
                possible = yum_max - yum_min + 1
                # print("clean, yum_pop, possible = ", clean, yum_pop, possible)
                so_far2 += possible
                if so_far2 >= m:
                    n = m - (so_far2 - possible)
                    yum = yum_min + n - 1
                    pop = yum_pop - yum
                    return [clean, yum, pop]
            break

    # so_far = 0
    # for s in range(3, N * 3 + 1):
    #     comb = get_comb(N, s)
        


N, K = map(int, input().split())
print(*solve(N, K))

