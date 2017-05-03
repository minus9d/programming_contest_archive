#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
パターンが少ないので場合分け
片側に予定が2つはいっているときだけ要検討、
予定をどうつなげても12時間を超えるようなら答えは4
"""

from array import *
from bisect import *
from collections import *
from fractions import *
from heapq import *
from itertools import *
from math import *
from re import *
from string import *

# small
def solve():
    AC, AJ = map(int, input().split())
    CDs = []
    JKs = []
    for c in range(AC):
        c, d = map(int, input().split())
        CDs.append((c,d))
    for j in range(AJ):
        j, k = map(int, input().split())
        JKs.append((j,k))
    CDs.sort()
    JKs.sort()

    # always AC >= AJ
    if AC < AJ:
        CDs, JKs = JKs, CDs
        AC, AJ = AJ, AC

    if AC == AJ == 0:
        return 2
    elif AC == 1 and AJ == 0:
        return 2
    elif AC == 1 and AJ == 1:
        return 2
    elif AC == 2 and AJ == 0:
        dist1 = CDs[1][1] - CDs[0][0]
        dist2 = (24 * 60) - (CDs[1][0] - CDs[0][1])
        if min(dist1, dist2) <= 720:
            return 2
        else:
            return 4
    else:
        print("error:")
        print(AC, AJ)

T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    print(solve())
