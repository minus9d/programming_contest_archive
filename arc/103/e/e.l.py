#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 必要条件まではわかったけど、必ず任意の木を構築できる
# という考えには至らず。
# https://betrue12.hateblo.jp/entry/2018/09/30/125042
# の図とC++コードを参考にする
#
# まず1文字目は必ず1。最初は以下のようなエッジを構築。
#                 2(top)
#                /
#               1
# "top"は、つぎの頂点がつながる先を表す。
#
# 2文字目が0の場合:  topは移動しない
#                 2(top)
#                / \
#               1   3
# 2文字目が1の場合:  topは移動する
#                   3(top)
#                  /
#                 2
#                /
#               1


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

def solve(S):
    # 必要条件の確認
    if S[-1] == '1':
        return -1
    if S[0] == '0':
        return -1
    size = len(S)
    i = 0
    j = size - 2
    while i < j:
        if S[i] != S[j]:
            return -1
        i += 1
        j -= 1

    # ここまで来た場合は必ず木を構築可能
    edges = []
    top = 0
    for i in range(size - 1):
        edges.append((top, i + 1))
        if S[i] == '1': 
            top = i + 1
    return edges

S = input()
ans = solve(S)
if ans == -1:
    print(ans)
else:
    for e in ans:
        print("{} {}".format(e[0] + 1, e[1] + 1))

