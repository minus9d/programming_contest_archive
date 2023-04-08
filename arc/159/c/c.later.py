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



def solve(N, As):
    arr1 = list(range(1, N + 1))
    arr2 = arr1[::-1]
    arr2[-2], arr2[-1] = arr2[-1], arr2[-2]

    As = As[:]

    # 解説を読んで修正
    # 本番では S % N == 0の場合しか考慮していなかった
    S = sum(As)
    if not (S % N == 0 or (S + N * (N + 1) // 2) % N == 0):
        return None

    ans = []

    # SがNの倍数でない場合には適当な順列を加えてNの倍数にする
    if S % N != 0:
        ans.append(arr1)
        for i in range(N):
            As[i] += arr1[i]

    # これでNの倍数になったはず
    assert sum(As) % N == 0
    
    # 平均を目指す
    while min(As) != max(As):
        S = sum(As)
        avg = S // N

        for ptr in range(N):
            # 平均より大きい場所を探す
            if As[ptr] > avg:
                # 平均より小さい場所を選ぶ
                for i in range(N):
                    if As[i] < avg:
                        ptr2 = i
                        break
    
                # ptrを1減らし、ptr2を1増やす
                arr3 = [0] * N
                arr4 = [0] * N
    
                arr3[ptr] = arr1[-2]
                arr4[ptr] = arr2[-2]
    
                arr3[ptr2] = arr1[-1]
                arr4[ptr2] = arr2[-1]
    
                j = 0
                for i in range(N):
                    if i != ptr and i != ptr2:
                        arr3[i] = arr1[j]
                        arr4[i] = arr2[j]
                        j += 1
    
                ans.append(arr3)
                ans.append(arr4)
    
                for i in range(N):
                    As[i] += arr3[i] + arr4[i]
    
                break
    return ans
    
            

N = int(input())
As = list(map(int, input().split()))
ret = solve(N, As)
if ret is None:
    print('No')
else:
    print('Yes')
    print(len(ret))
    for r in ret:
        print(*r)



