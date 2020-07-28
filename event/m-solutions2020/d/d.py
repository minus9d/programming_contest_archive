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

N = int(input())
As = list(map(int, input().split()))

# peak = n - 1
# for n in range(N - 2, -1, -1):
#     if As[n] > As[n + 1]:
#         peak = n
#     else:
#         break

def solve_slow(N, As):
    nums = [0, 1, 2]

    ans = 0
    for comb in product(nums, repeat=N):
        money = 1000
        stock = 0
        for c, a in zip(comb, As):
            # sell
            if c == 0:
                money += a * stock
                stock = 0
            # buy
            elif c == 1:
                stock += money // a
                money = money % a
            else:
                pass
            # print("c, money, stock = ", c, money, stock)
        # print()
        ans = max(ans, money)

    return ans
                

def solve_fast(N, As):
    def uniq(As):
        ret = []
        for a in As:
            if not ret:
                ret.append(a)
            else:
                if ret[-1] != a:
                    ret.append(a)
        return ret
    
    As = uniq(As)
    N = len(As)
    
    ans = 0
    money = 1000
    stock = 0
    for n in range(N):
        ans = max(ans, money + stock * As[n])
    
        if n == N - 1:
            break
    
        if As[n] < As[n + 1]:
            stock_diff, money = divmod(money, As[n])
            stock += stock_diff
            # stock, money = divmod(money, As[n])
        elif As[n] > As[n + 1]:
            money += stock * As[n]
            stock = 0
        # print("m, s = ", money, stock)
    
    return ans

print(solve_fast(N, As))
# print(solve_slow(N, As))

# while True:
#     N = 10
#     As = [random.randint(1, 10) for _ in range(N)]
#     s = solve_slow(N, As)
#     f = solve_fast(N, As)
#     if s != f:
#         print(N)
#         print(As)
#         s = solve_slow(N, As)
#         f = solve_fast(N, As)
#         break
#     else:
#         print("ok")



