#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 本番後に自力で回答
#
# 左の列から順に見ていく
#
# 例えば、以下の盤面にて、「CCDD」の部分に何が入るかを考える。
#   AACC
#   BBDD
# AAがa色、BBがb色で塗られているとすると、塗り方は
#   aabb  aacc  aabb
#   bbaa  bbaa  bbcc
# の3通り。なので3をかける

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

MOD = 1000000007
N = int(input())
S1 = input()
S2 = input()

i = 0
prev = None
ans = 1
while i < N:
    if S1[i] == S2[i]:
        if prev is None:
            ans *= 3
        if prev == 'ver':
            ans *= 2
        if prev == 'hor':
            pass
        prev = 'ver'
        i += 1
    else:
        if prev is None:
            ans *= 6
        if prev == 'ver':
            ans *= 2
        if prev == 'hor':
            ans *= 3
        prev = 'hor'
        i += 2
    ans %= MOD
print(ans)
