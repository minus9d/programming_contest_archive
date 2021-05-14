#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from bisect import *
from collections import *
from itertools import *

import numpy as np
from numba import njit

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
        

def get_comb(N, s):
    m = N - 1
    naive = m * (m - 1) // 2

    


def get_arr(N):
    """
    (1 + x + ... + x^(N-1)) ^ 3
    の各係数の値を返す。数式は
    https://oeis.org/A109439
    をそのまま使用
    """
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


def get_arr2(N):
    """
    (1 + x + ... + x^(N-1)) ^ 3
    の各係数の値を返す。DPを利用
    """
    # e.g. N = 5のとき
    # 1回目: 0  1  1  1  1  1  0  0  0  0  0  0  0  0  0  0
    # 2回目: 0  0  1  2  3  4  5  4  3  2  1  0  0  0  0  0
    # 3回目: 0  0  0  1  3  6 10 15 18 19 18 15 10  6  3  1

    arr = np.zeros((3, N * 3 + 1), dtype=np.int)

    @njit
    def internal(arr):
        arr[0, 1:N+1] = 1
        for i in range(2):
            # 累積和
            cumsum = np.cumsum(arr[i])
            for j in range(i + 1, N * (i + 2) + 1):
                end = j - 1
                begin = end - N
                if begin < 0:
                    arr[i + 1, j] = cumsum[end]
                else:
                    arr[i + 1, j] = cumsum[end] - cumsum[begin]
        return arr[2][3:]

    return internal(arr)


# for n in range(1, 10):
#     print(get_arr(n))
#     print()

@njit
def find_ans(arr):
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


def solve(N, K):

    # N = 5のとき
    # (1 + x + x^2 + x^3 + x^4) ^ 3
    # の係数を考える

    # https://oeis.org/A109439 の数式をそのまま実装
    # arr1 = get_arr(N)

    # DPで係数を取得（競技プログラミング的にはこちら）
    arr2 = get_arr2(N)

    # arr1を使ってもACすることを確認済み (https://atcoder.jp/contests/abc200/submissions/22439979)
    # ここではarr2を使う
    arr = arr2

    return find_ans(arr)


N, K = map(int, input().split())
print(*solve(N, K))

