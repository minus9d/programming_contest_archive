#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 終了後、解説を見て実装
# 壊れているworkerはせいぜい15台である制約を利用。
# 5回分のクエリを、そのビットを前から見ていくと0 1 2 .. 31を繰り返すように構成すると
# どのworkerが壊れたかを完全特定できる。
# (もし15台のworkerが連続して壊れているような場合でも、かならず32の中に納まる)
#
# 実装は2種類試した。どちらでもAC。新手法とあるほうがわかりやすい実装なはず。
#
# インタラクティブ問題のメモ
#   標準出力にはprint2(), 標準エラー出力にはprinte()を使う
#
#   デバッグ用ツールを動かすには
#     python interactive_runner.py python testing_tool.py 1 -- ./d.later.py
#   などとする。1の部分には0, 1をいれる
#     Judge return code: 0
#     Solution return code: 0
#   となればOK

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


def print2(*args, **kwargs):
    print(*args, **kwargs)
    sys.stdout.flush()


def printe(*args, **kwargs):
    print(*args, **kwargs, file=sys.stderr)
    sys.stderr.flush()


def solve():

    N, B, F = map(int, input().split())
    printe("N, B, F =", N, B, F)

    nums = []
    for n in cycle(range(32)):
        nums.append(n)
        if len(nums) == N:
            break

    responses = []
    for f in range(5):
        query = ''
        for n in nums:
            if n & (1 << f):
                query += '1'
            else:
                query += '0'
        print2(query)
        printe("query:", query)
        responses.append(input())

    for r in responses:
        printe(r)

    # another solution
    groups = []
    group = []
    prev = -1
    for cur in range(len(responses[0])):
        num = 0
        for i, r in enumerate(responses):
            num += (1 << i) * (r[cur] == '1')
        if num > prev:
            group.append(num)
        else:
            groups.append(group)
            group = [num]
        prev = num
    if group:
        groups.append(group)

    # # 新手法
    # newans = []
    # offset = 0
    # for group in groups:
    #     for i in range(32):
    #         if i not in group:
    #             newans.append(offset + i)
    #     offset += 32
    # printe("groups = ")
    # for g in groups:
    #     printe(g)
    # printe("new ans = ", newans)
    # newans = newans[:B]
    # print2(*newans)

    # 旧手法
    ans = []
    cur = 0
    for n in range(N):
        if cur >= len(responses[0]):
            ans.append(n)
        else:
            num = 0
            for i, r in enumerate(responses):
                num += (1 << i) * (r[cur] == '1')
            if num != (n % 32):
                ans.append(n)
            else:
                cur += 1

    printe("ans = ", *ans)
    # printe("len(ans) = ", len(ans))
    print2(*ans)

    # エラーチェック
    verdict = int(input())
    if verdict != 1:
        printe("fail...", verdict)
        sys.exit(0)


T = int(input())
for testcase in range(T):
    solve()
sys.exit(0)
