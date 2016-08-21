#!/usr/bin/env python3
# -*- coding: utf-8 -*-

n = int(input())

def func(n):
    if n % 2 == 1:
        b = (n ** 2 - 1) // 2
        c = (n ** 2 + 1) // 2
    else:
        b = (n // 2) ** 2 - 1
        c = (n // 2) ** 2 + 1
    return b,c

if n <= 2:
    print(-1)
else:
    b,c = func(n)
    print(b,c)

# for n in range(3,10000000):
#     b,c = func(n)
#     assert n ** 2 + b ** 2 == c ** 2
