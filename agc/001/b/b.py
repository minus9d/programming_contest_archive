#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import functools

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a
    
# @functools.lru_cache(maxsize = None)
# def func(N, X):
#     g = gcd(N, X)
#     if g == 1:
#         if X > N // 2:
#             return func(N, N - X)
#         if N == 2:
#             return 3
#         if N == 3:
#             return 6
#         return X * 3 + func(N-X, X)
#     else:
#         return g * func(N//g, X//g)


def func_fast(N, X):
    g = gcd(N, X)
    if g == 1:
        return 3 * N - 3
    else:
        return g * func_fast(N // g, X // g)

N,X = map(int,input().split())
print(func_fast(N,X))
        
