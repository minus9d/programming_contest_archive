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

            
def solve(A, B):

    if A == B == 10**9 - 5:
        solve_small1(A, B)
    elif A == B == 10**9 - 50:
        solve_small2(A, B)



T, A, B = map(int, input().split())
for testcase in range(T):
    solve(A, B)
sys.exit(0)
