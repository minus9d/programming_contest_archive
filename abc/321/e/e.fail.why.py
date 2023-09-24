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

def solve2(N, X, depth):
    """木の下にある分だけ数える
    """
    if depth == 0:
        return 1
    if depth < 0:
        return 0

    # 頂点XからK下にある頂点は、[mn, mx]
    mn = X * 2 ** depth
    mx = min(mn + 2 ** depth - 1, N)

    # print(f"from {X}, mn and mx are {mn}, {mx}")
    num = max(0, mx - mn + 1)
    
    return num

def has_parent(N, X, depth):
    """depthだけ上に親がいるかを見る
    """
    for i in range(depth):
        X //= 2
    return int(X >= 1)
    

def get_sib(parent, cur):
    child1 = parent * 2
    child2 = child1 + 1
    if child1 == cur:
        return child2
    else:
        return child1


def solve_slow(N, X_, K):
    ans = 0
    for i in range(1, N + 1):
        # iとXとの距離を求める
        j = i
        X = X_

        tmp = 0
        while j != X:
            if j < X:
                X //= 2
                tmp += 1
            else:
                j //= 2
                tmp += 1

        print(f"{i} and {X} distance = {K}")
        if tmp == K:
            
            ans += 1
    return ans
                


def solve(N, X, K):

    if K > 122:
        return 0

    ans = 0
    
    # 自分より下にあるものだけ数える
    ans1 = solve2(N, X, K)
    ans += ans1
    # print("ans1 = ", ans1)

    # 自分の親を数える
    if K > 0:
        ans += has_parent(N, X, K)
        # print("parent = ", has_parent(N, X, K))


    # 一つずつ上に登っていく
    cur = X
    while cur != 1:
        parent = cur // 2
        sib = get_sib(parent, cur)
        
        K2 = K - 2
        if K2 < 0:
            break

        if sib <= N:
            ans2 = solve2(N, sib, K2)
            # print("ans2 = ", ans2)
            ans += ans2

        cur = parent
        K -= 1

    return ans


import random
import time

# random.seed(0)
# while True:
#     N = random.randint(1, 100000)  # 10 ** 18)
#     X = random.randint(1, N)
#     K = random.randint(1, 70)
#     mine = solve(N, X, K)
#     gt = solve_slow(N, X, K)


#     if mine != gt:
#         print("error!")
#         print(N, X, K)
#         print("mine, gt = ", mine, gt)
#         sys.exit(0)
#     else:
#         print("ok")


# t1 = time.time()
# for t in range(10**5):
#     N = random.randint(10 ** 17, 10 ** 18)
#     X = random.randint(1, N)
#     K = random.randint(N // 10, N)
#     mine = solve(N, X, K)
# t2 = time.time()
# print("time:", t2 - t1)
    
   
    

T = int(input())
for t in range(T):
    N, X, K = map(int, input().split())
    ans = solve(N, X, K)
    print(ans)





