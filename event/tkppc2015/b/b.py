#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
mx = -1
ans = 0
for i, _ in enumerate(range(N)):
    num = int(input())
    if num > mx:
        mx = num
        ans = i
print(ans + 1)

    
