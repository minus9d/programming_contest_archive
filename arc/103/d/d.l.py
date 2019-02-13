#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 解説を読んで回答
#
# https://betrue12.hateblo.jp/entry/2018/09/30/125042
# がわかりやすい
#
# 任意の長さを表現するには1, 2, 4, 8, ...という2のべき乗の列が使えそうなこと、
# X軸とY軸の条件を満たすために座標変換を行うことがポイント

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

def solve(N, XYs):

    # 偶奇が一致しない場合は構成不可能
    mod2 = [(x + y) % 2 for x, y in XYs]
    if min(mod2) != max(mod2):
        print(-1)
        return

    # 使う腕の長さは基本的に1, 2, 4, 8, ...。
    # ただしmod 2 = 0の場合は長さ1の腕を一本追加
    arms = [2 ** x for x in range(31)]
    if mod2[0] == 0:
        arms = [1] + arms
    arms.reverse()

    print(len(arms))
    print(*arms)
    for x, y in XYs:
        # 座標変換
        u, v = x + y, x - y
        # print("===u, v, x, y = {}, {}, {}, {}===".format(u, v, x, y))

        ans = ''
        for arm in arms:

            before_x = (u + v) // 2
            before_y = (u - v) // 2

            if u > 0:
                u -= arm
            else:
                u += arm
            if v > 0:
                v -= arm
            else:
                v += arm

            after_x = (u + v) // 2
            after_y = (u - v) // 2

            # 目標地点から原点に向かう方向に移動しているので
            # 記号も逆になるのに注意
            if before_x == after_x:
                if before_y < after_y:
                    ch = 'D'
                else:
                    ch = 'U'
            else:
                if before_x < after_x:
                    ch = 'L'
                else:
                    ch = 'R'
            ans += ch

        print(ans)

        # 検算
        assert u == 0 and v == 0
        pos_x = pos_y = 0
        for d, arm in zip(ans, arms):
            if d == 'U': pos_y += arm
            elif d == 'D': pos_y -= arm
            elif d == 'L': pos_x -= arm
            elif d == 'R': pos_x += arm
        assert x == pos_x
        assert y == pos_y


N = int(input())
XYs = []
for n in range(N):
    x, y = map(int, input().split())
    XYs.append((x, y))
solve(N, XYs)
