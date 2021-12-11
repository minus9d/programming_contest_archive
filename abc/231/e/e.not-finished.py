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


sys.setrecursionlimit(10 ** 9)



def solve(N, X, A):
    ans = 0
    for i in range(N - 1):
    
        mod = X % A[i + 1]
    
        # print("A[i], A[i+1], remain X, mod = ", A[i], A[i+1], X, mod)
    
        # 上ので払えるなら払う
        if mod == 0:
            continue
    
        # もしA[i]で払う場合
        num1 = mod // A[i]
    
        # A[i+1]以降で払う場合
        num2 = 1 + (A[i + 1] - mod) // A[i]
    
        print("num1, 2 = ", num1, num2)
        if num1 < num2:
            ans += num1
            X -= A[i] * num1
        else:
            ans += num2 - 1
            X += A[i + 1] - mod
    
        print("ans, X = ", ans, X)
    # print("remain X: ", X)
    assert X % A[-1] == 0
    ans += X // A[-1]
    return ans


def solve_slow(N, X, A):
    if N == 1:
        return X

    ans = 1e18
    ans_comb = None

    nums = list(range(9))
    # 高価な高価からの選択数を決め打ち
    for comb in product(nums, repeat=N):
        money_sum = 0

        cnt = 0
        for num, money in zip(comb, A):
            money_sum += num * money
            cnt += num

        if money_sum < X:
            continue


        # おつりを計算
        Y = money_sum - X
        for a in reversed(A):
            tmp = Y // a
            cnt += tmp
            Y -= a * tmp

        if cnt < ans:
            ans = cnt
            ans_comb = comb[:]


    print(ans, ans_comb, money_sum)
    return ans
            

N, X  = map(int, input().split())
A = list(map(int, input().split()))
print(solve(N, X, A))

random.seed(77)

# while True:
#     N = random.randint(3, 4)
#     A = []
#     tmp = 1
#     for n in range(N):
#         A.append(tmp)
#         tmp *= random.randint(2, 5)
#     X = random.randint(1, 40)
#     mine = solve(N, X, A)
#     gt = solve_slow(N, X, A)

#     if gt == 1e18:
#         continue

#     if mine != gt:
#         print("error")
#         print(N, X, A, mine, gt)
#         break
