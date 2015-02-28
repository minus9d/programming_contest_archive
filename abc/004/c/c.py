#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
N %= 30

array = list(range(1, 7))
for n in range(0, N):
    array[n % 5], array[(n % 5) + 1] = array[(n % 5) + 1], array[n % 5]
print("".join(map(str,array)))
