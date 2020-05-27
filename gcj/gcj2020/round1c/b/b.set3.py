#!/usr/bin/env python3
# -*- coding: utf-8 -*-

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


def solve_greedy(U, QR):
    letters = set()
    c = Counter()
    for q, r in QR:
        for ch in r:
            c[ch] += 1
            break
        for ch in r:
            letters.add(ch)
    ans = ""
    for e in c.most_common():
        ans += e[0]

    # 出てこなかった文字が'0'
    for l in letters:
        if l not in ans:
            ans = l + ans
            break

    return ans

# def encode(N, D):
#     N_str = str(N)
#     ret = ""
#     for ch in N_str:
#         ch_n = int(ch)
#         ret += D[ch_n]
#     return ret

# def simulate():
#     D = ''.join(random.sample(string.ascii_uppercase, 10))
#     print("D: ", D)
#     U = 16

#     QR = []
#     for _ in range(10000):
#         # クエリ。set3では秘密
#         M = random.randint(1, 10 ** U - 1)

#         N = random.randint(1, M)
#         # Nをエンコード
#         R = encode(N, D)
#         print(M, N, R)

#         QR.append((M, R))

#     myans = solve_greedy(U, QR)
#     if myans != D:
#         print("error! myans, gt = ", myans, D)
#     else:
#         print("correct!")

# simulate()

def solve():
    U = int(input())

    QR = []
    for rep in range(10000):
        q, r = input().split()
        q = int(q)
        QR.append((q, r))
    print(solve_greedy(U, QR))

    return


T = int(input())
for testcase in range(T):
    print("Case #{}: ".format(testcase+1), end="")
    solve()
