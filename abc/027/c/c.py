#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

N = int(input())
flag = True
if N == 1:
    print('Aoki')
else:
    s = 2
    p = 1
    while True:
        p *= 4
        t = s + p - 1
        if s <= N <= t:
            print("Takahashi")
            break
        s += p
        t += p
        if s <= N <= t:
            print("Aoki")
            break
        s += p
        

# 以下は実験用        
# @functools.lru_cache(maxsize = None)
# def win(x, n):
#     if x > n:
#         return True
#     elif 2 * x > n:
#         return False
#     elif 2 * x == n:
#         return True
#     else:
#         if not win(2*x, n) or not win(2*x+1, n):
#             return True
#         else:
#             return False

# for n in range(1, 1000):
#     print(n, ":", end="")
#     if win(1, n):
#         print('Takahashi')
#     else:
#         print('Aoki')


