#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
Cについて、
  ・actとactの間の時間(gap)を列挙。
  ・短いgapのうち、以下の条件を満たすものがあれば、そのgapを塗り潰す
      1. その時間にJがactを持たない
      2. gapを塗り潰しても合計時間が12時間を超えない
Jについても同様。
gapをぬりつぶしたあとに残るactについて、交代数を数える (get_ans()を参照）。

実装の注意点
 ・最初のactと最後のactとが繋がっている場合がある。
　　最初にこれらをマージしてしまうとよい。(本番では気づかなかった)
 ・CのactとJのactを同じ時間分だけずらす(本番で片方のみずらしてしまった)
 ・ずらしたあとのactの最終時刻が0ではなく24*60となるようにする
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

def included(g_start, g_end, JKs):
    for j, k in JKs:
        if g_start <= j <= g_end or g_start <= k <= g_end:
            return True
    return False


def make_gaps(CDs, JKs):
    gaps = []
    for i in range(len(CDs)-1):
        g_start = CDs[i][1]
        g_end = CDs[i+1][0]
        if not included(g_start, g_end, JKs):
            gaps.append(g_end - g_start)
    # corner case: around midnight
    if len(CDs) >= 1 and \
       not included(CDs[-1][1], 24*60, JKs) and \
       not included(0, CDs[0][0], JKs):
        gaps.append(24 * 60 - CDs[-1][1] + CDs[0][0])

    return gaps

def calc_total(CDs):
    total = 0
    for c, d in CDs:
        total += d - c
    return total

def count_mergeable_range(c_gaps, CDs):
    c_total = calc_total(CDs)
    ret = 0
    for gap in c_gaps:
        if gap + c_total <= 720:
            ret += 1
            c_total += gap
        else:
            break
    return ret

def get_ans(act1, act2):
    if act1 < act2:
        act1, act2 = act2, act1

    if act1 == 0:
        # corner case: actが0の場合でも交代が必要
        return 2
    else:
        return act1 * 2

def solve2(CDs, JKs):
    c_gaps = make_gaps(CDs, JKs)
    j_gaps = make_gaps(JKs, CDs)

    c_gaps.sort()
    j_gaps.sort()

    act1 = len(CDs) - count_mergeable_range(c_gaps, CDs)
    act2 = len(JKs) - count_mergeable_range(j_gaps, JKs)
    return get_ans(act1, act2)

def minus_time(c, time):
    c -= time
    if c < 0:
        c += 24 * 60
    return c

def create_new_cds(CDs, start_time):
    new_CDs = []
    for c, d in CDs:
        new_c = minus_time(c, start_time)
        new_d = minus_time(d, start_time)
        if new_d == 0:
            new_d += 24 * 60
        new_CDs.append((new_c, new_d))
            
    return new_CDs


def can_delete_last(CDs):
    return len(CDs) >= 2 and CDs[0][0] == 0 and CDs[-1][1] == 1440


def delete_last(CDs, start_time):
    # actを繋げる場合：時間をずらし、かつ2つのactを繋げる
    if can_delete_last(CDs):
        new_CDs = create_new_cds(CDs, start_time)
        new_CDs = new_CDs[1:]
        new_CDs[-1] = (0, (CDs[0][1] - CDs[0][0]) + (CDs[-1][1] - CDs[-1][0]))
        new_CDs.sort()
        return new_CDs
    # actを繋げない場合：単に時間をずらす
    else:
        new_CDs = create_new_cds(CDs, start_time)
        new_CDs.sort()
        return new_CDs


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

    # 1日の最後のactと1日の最初のactが繋がっている場合、1日の最後のactの開始時間を0:00とみなす
    if can_delete_last(CDs):
        start_time = CDs[-1][0]
    elif can_delete_last(JKs):
        start_time = JKs[-1][0]
    else:
        start_time = 0

    # actの開始時間をずらしつつ、かつ繋がっているactを繋げる
    CDs = delete_last(CDs, start_time)
    JKs = delete_last(JKs, start_time)

    ans = solve2(CDs, JKs)
    return ans

T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    print(solve())
