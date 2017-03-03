#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from itertools import *
import sys

N = int(input())
marks = input()
marks = [ 1 if mark == 'x' else 0 for mark in marks]

for comb in product([0, 1], repeat=2):
    arr = [None for _ in range(N)]
    arr[:2] = comb
    for i in range(2, N):
        arr[i] = arr[i-2] ^ arr[i-1] ^ marks[i-1]
    if (arr[-2] ^ arr[-1] ^ arr[0] == marks[-1]) \
       and (arr[-1] ^ arr[0] ^ arr[1] == marks[0]) \
       and (arr[0] ^ arr[1] ^ arr[2] == marks[1]):
        print(''.join('S' if x == 0 else 'W' for x in arr))
        sys.exit(0)
print(-1)


