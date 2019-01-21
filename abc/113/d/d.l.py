#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本番後に自力AC
#
# 素直にDP

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

H, W, K = map(int, input().split())

MOD = 1000000007

def solve(H, W, K):
    if W == 1:
        return 1

    # dp = np.zeros((H+1, W), dtype=np.int64)
    dp = [[0 for _ in range(W)] for _ in range(H+1)]
    dp[0][0] = 1

    for h in range(1, H+1):
        # 横線を引ける可能性があるのは2^(W-1)通り
        # 実際は連続した横線は引けないのでもう少し少なくなる
        for i in range(1 << (W-1)):
            # 連続する横線がある場合はスキップ
            ok = True
            for j in range(1, W-1):
                if (i & (1 << j)) and (i & (1 << (j-1))):
                    ok = False
            if not ok:
                continue

            # print("i: ", end="")
            # for j in range(W-1):
            #     print(int(bool(i & (1 << j))), end="")
            # print()
            
            # DP
            # 各縦線についてループ
            for j in range(W):
                # 左側の縦線との間に横線あり
                if j != 0 and i & (1 << (j - 1)):
                    dp[h][j] += dp[h-1][j-1]
                    dp[h][j] %= MOD
                # 右側の縦線との間に横線あり
                elif j != W-1 and i & (1 << j):
                    dp[h][j] += dp[h-1][j+1]
                    dp[h][j] %= MOD
                # 横線なし
                else:
                    dp[h][j] += dp[h-1][j]
                    dp[h][j] %= MOD

    return dp[H][K-1]

print(solve(H, W, K))

