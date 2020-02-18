#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
コンテスト後に解説記事を見てAC
Python 3だとTLE
"""

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

def solve(N_str):
    """
    https://betrue12.hateblo.jp/ の通り実装

    上の桁から順番に見ていく
    dp[i][j] =
      上から i 桁目までの硬貨の支払いとお釣りを処理し終わって、
      N の i 桁目までの金額よりも j 枚分多く支払っているときの、
      これまでの支払い・お釣り硬貨の最小合計枚数
    """
    N_str = '0' + N_str
    dp = [[0] * 2 for _ in range(len(N_str))]

    # 0376円のとき

    # dp[1][0] = 0       0円払う(0)
    # dp[1][1] = 1    1000円払う(1)
    #
    # dp[2][0] = 3    0円の状態から300円払う(3)  vs  1000円の状態から700円お釣りをもらう(8)
    # dp[2][1] = 4    0円の状態から400円払う(4)  vs  1000円の状態から600円お釣りをもらう(7)
    #
    # dp[3][0] = 7    300円の状態から追加で70円払う(3+7) vs 400円の状態から30円もらう(4+3)
    # dp[3][1] = 6    300円の状態から追加で80円払う(3+8) vs 400円の状態から20円もらう(4+2)
    #
    # dp[4][0] = 10   370円の状態から追加で6円払う(7+6) vs 380円の状態から4円もらう(6+4)
    # dp[4][1] = 9    370円の状態から追加で7円払う(7+7) vs 380円の状態から3円もらう(6+3)

    for i, ch in enumerate(N_str):
        if i == 0:
            dp[0][0] = 0
            dp[0][1] = 1
        else:
            dp[i][0] = min(dp[i - 1][0] + int(ch),
                           dp[i - 1][1] + 10 - int(ch))
            dp[i][1] = min(dp[i - 1][0] + int(ch) + 1,
                           dp[i - 1][1] + 9 - int(ch))

    return dp[len(N_str) - 1][0]


def wrong(N_str):
    """最初に間違って書いた貪欲
    1の位から見ていき、0~4なら支払い、5~9なら10払ってお釣りをもらう

    N = 65のとき、
    この関数だと70払って5お釣りをもらうことになるが
    実際は100払って35お釣りをもらうべきなので誤り
    """
    N_str = N_str[::-1]
    ans = 0
    prev = 0
    for ch in N_str:
        n = int(ch)
        n += prev
        if n <= 5:
            ans += n
            prev = 0
        else:
            ans += 10 - n
            prev = 1
    ans += prev    
    return ans

# for n in range(1, 101):
#     print()
#     n_str = str(n)
#     w = wrong(n_str)
#     gt = solve(n_str)
#     if w != gt:
#         print("n, gt, wrong = ", n, gt, w)

N_str = input()
print(solve(N_str))
