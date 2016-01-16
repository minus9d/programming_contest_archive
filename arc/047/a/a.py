#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,L = [int(a) for a in input().split()]

s = input()

tab = 1
ans = 0
for ch in s:
    if ch == '+':
        tab += 1
        if tab > L:
            ans += 1
            tab = 1
    else:
        tab -= 1
print(ans)
