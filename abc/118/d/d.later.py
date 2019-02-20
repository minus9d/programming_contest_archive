#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 自力実装できず
#
# 解説PDFが理解できなかったので
# http://drken1215.hatenablog.com/entry/2019/02/16/224100
# を参考に実装

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


def str_max(s1, s2):
    if len(s1) > len(s2):
        return s1
    elif len(s1) < len(s2):
        return s2
    if s1 > s2:
        return s1
    else:
        return s2


def main():
    N, M = map(int, input().split())
    As = list(map(int, input().split()))
    
    needs = [0,2,5,5,4,5,6,3,7,6]
    need_to_ch = {}
    for a in sorted(As):
        need = needs[a]
        need_to_ch[need] = str(a)
    
    dp = [None for _ in range(N + 1)]
    dp[0] = ''
    for i in range(1, N + 1):
        for need, ch in need_to_ch.items():
            if i - need < 0 or dp[i - need] is None:
                continue
            # ここで文字列をソートしたくなるがソートする必要はない
            # もしdp[i]に11114が入っているとき、candが41111なら
            # dp[i]は41111により上書きできる
            cand = dp[i - need] + ch
            if dp[i] is None:
                dp[i] = cand
            else:
                dp[i] = str_max(dp[i], cand)
        # print("dp[{}] = {}".format(i, dp[i]))
    print(dp[N])


main()
