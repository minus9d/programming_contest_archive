#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 自力AC
#
# Nを減ずる操作は、別に最大値をもつ要素からではなく
# 好きな順番で行っても結果は変わらないことに着目。
# 以下を繰り返すだけ。なぜ600点かと思うほど瞬間的に解けた
#   各要素について、Nを減ずる操作を行えるだけ行う。その回数を記録しておく
#   各要素について、他の要素で行った減算操作の回数だけ値を増やす

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

N = int(input())
As = list(map(int, input().split()))

ans = 0
while True:
    taken = [0] * N
    for i, a in enumerate(As):
        taken[i] = a // N
        As[i] -= taken[i] * N
    # print("===")
    # print(As)
    # print(taken)

    taken_sum = sum(taken)
    if taken_sum == 0:
        break
    ans += taken_sum
    for i in range(N):
        As[i] += (taken_sum - taken[i])
print(ans)    
