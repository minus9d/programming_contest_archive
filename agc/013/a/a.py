#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
As = list(map(int, input().split()))

inc = None
prev = None
ans = 0
for i, a in enumerate(As):
    if i == 0:
        ans += 1
    elif inc is None:
        if a > prev:
            inc = True
        elif a < prev:
            inc = False
    else:
        if (inc and a < prev) or (inc == False and a > prev):
            ans += 1
            inc = None
    prev = a
print(ans)
