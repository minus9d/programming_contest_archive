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

def solve(A, B):

    if A == B == 10**9 - 5:
        solve_small1(A, B)



T, A, B = map(int, input().split())
for testcase in range(T):
    solve(A, B)
sys.exit(0)
