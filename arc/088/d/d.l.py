#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本番後に自力AC
#
# 文字列の中央部分は、Kが大きいと変更ができないことに着目。
# 「文字列の中央に何個連続した文字があるか」とKとの関係を実験で求めた。
#
# oは同じ文字。oのとなりにあるxのうち少なくとも一方はoとは異なる文字とする。
#
# 奇数の場合
#       S     : K
#   x x o x x : 3
#   x o o o x : 4
#   o o o o o : 5
# 偶数の場合
#      S    : K
#   x x x x : 2
#   x o o x : 3
#   o o o o : 4


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

S = input()
size = len(S)
if len(S) % 2 == 0:
    ans = size // 2
    base = S[size // 2]
    for i in range(size // 2):
        if S[size // 2 - 1 - i] == S[size // 2 + i] == base:
            ans += 1
        else:
            break
    print(ans)
else:
    ans = size // 2 + 1
    base = S[size // 2]
    for i in range(size // 2):
        if S[size // 2 - 1 - i] == S[size // 2 + 1 + i] == base:
            ans += 1
        else:
            break
    print(ans)
    
