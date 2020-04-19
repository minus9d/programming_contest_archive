#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


def solve_small1(A, B):
    for y in range(-5, 6):
        for x in range(-5, 6):
            print2(x, y)
            res = input()
            if res == "CENTER":
                return

def in_or_out(p1, p2, R):
    return (p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2 <= R ** 2


def filter_candidates(candidates, res, x, y, R):
    ret = []
    if res == "HIT":
        for cand_x, cand_y in candidates:
            if 0 < (cand_x - x) ** 2 + (cand_y - y) ** 2 <= R ** 2:
                ret.append((cand_x, cand_y))
    elif res == "MISS":
        for cand_x, cand_y in candidates:
            if 0 < (cand_x - x) ** 2 + (cand_y - y) ** 2 > R ** 2:
                ret.append((cand_x, cand_y))
    return ret

def solve_small2(A, B):
    """
    * 中心点の候補101^2個を生成
    * 調べる価値のあるクエリを手動で200個ほど決定
    * クエリを投げて得られた結果から中心点の候補を絞り込む。
        * ただしクエリを投げても情報量0なことがわかっているならそのクエリは投げない
    * 十分候補を絞り込めれば全探索
    """
    candidates = []
    for y in range(-50, 51):
        for x in range(-50, 51):
            candidates.append((x, y))

    L = int(A / math.sqrt(2))

    # queries = [(L, L), (L, -L), (-L, L), (-L, -L)]
    queries = []
    for i in range(5):
        add = 50 // 5 + i

        queries.append((L, L))
        queries.append((L, L + add))
        queries.append((L + add, L))
        queries.append((L + add, L + add))

        queries.append((L, -L))
        queries.append((L, -L-add))
        queries.append((L+add, -L))
        queries.append((L+add, -L-add))

        queries.append((-L, L))
        queries.append((-L, L+add))
        queries.append((-L-add, L))
        queries.append((-L-add, L-add))

        queries.append((-L, -L))
        queries.append((-L, -L-add))
        queries.append((-L-add, -L))
        queries.append((-L-add, -L-add))

        for offset in (0, 25, -25):
            queries.append((A, offset))
            queries.append((A+add, offset))
            queries.append((A-add, offset))

            queries.append((-A, offset))
            queries.append((-A-add, offset))
            queries.append((-A+add, offset))

            queries.append((offset, A))
            queries.append((offset, A+add))
            queries.append((offset, A-add))

            queries.append((offset, -A))
            queries.append((offset, -A-add))
            queries.append((offset, -A+add))


    queries = set(queries)
    printe("query len = ", len(queries))

    def has_meaning(q, candidates, r):
        inc = 0
        exc = 0
        for c in candidates:
            if in_or_out(q, c, r):
                inc += 1
            else:
                exc += 1
            if inc != 0 and exc != 0:
                return True
        return False

    queries = list(queries)
    random.shuffle(queries)

    query_num = 0
    for q in queries:

        # 意味のないクエリであれば投げない
        # （これがないとクエリ数が超過してしまう）
        if not has_meaning(q, candidates, A):
            continue

        query_num += 1
        print2(*q)
        res = input()
        # printe("q, res: ", q, res)
        candidates = filter_candidates(candidates, res, q[0], q[1], A)

        # 十分？
        if 300 - query_num >= len(candidates):
            printe("ok cand num = ", len(candidates))
            break


    printe("len(cands) = ", len(candidates))
    # printe("cands = ", candidates)
    for cand in candidates:
        print2(*cand)
        res = input()
        if res == "CENTER":
            # printe("ans = ", *cand)
            return

        

def solve_large(A, B):
    """
    https://twitter.com/snuke_/status/1251942812775403520
    を参考に実装
    """

    # この4点は必ずいずれかがHIT
    L = 10 ** 9 // 4
    queries = [(L, L), (L, -L), (-L, L), (-L, -L)]
    for q in queries:
        print2(*q)
        res = input()
        if res == "CENTER":
            return
        if res == "HIT":
            hit = q
            break

    def binsearch(ok, ng):
        """HITする点(ok)とMISSする点(ng)を二分探索し、
        HITするぎりぎりの点を探す
        もし途中でCENTERを見つけてしまった場合はNoneを返す
        """

        for i in range(70):
            mid = ((ok[0] + ng[0]) // 2,
                   (ok[1] + ng[1]) // 2)
            print2(*mid)
            res = input()
            if res == "CENTER":
                return None
            elif res == "HIT":
                ok = mid
            else:
                ng = mid
        return ok

    # hitから上下左右にHITとMISSの境界を探す
    # 途中で正解が見つかっていたらNone
    #
    # 本来はHITとMISSの境界が存在しない、つまりHITだけが続く場合
    # （例：答が(center_x, center_y, r) = (10**9 // 4, 10**9 // 4, 10**9 // 2))）
    # も考慮すべきところだが、運良く考慮しなくても通る
    up = binsearch(hit, (hit[0], 10**9))
    if up is None:
        return
    down = binsearch(hit, (hit[0], -10**9))
    if down is None:
        return
    left = binsearch(hit, (-10**9, hit[1]))
    if left is None:
        return
    right = binsearch(hit, (10**9, hit[1]))
    if right is None:
        return

    printe(up, down, left, right)

    # centerの大体の座標が求まる
    center_x = (left[0] + right[0]) // 2
    center_y = (up[1] + down[1]) // 2

    # 誤差を考慮して周辺を探す
    for x in range(center_x - 1, center_x + 2):
        for y in range(center_y - 1, center_y + 2):
            print2(x, y)
            res = input()
            if res == "CENTER":
                return

            
def solve(A, B):

    if A == B == 10**9 - 5:
        solve_small1(A, B)
    elif A == B == 10**9 - 50:
        solve_small2(A, B)
    else:
        solve_large(A, B)



T, A, B = map(int, input().split())
for testcase in range(T):
    solve(A, B)
sys.exit(0)
