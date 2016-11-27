#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
As = []
for i in range(N):
    As.append(int(input()))

mn = 1
ans = 0
for a in As:
    if mn == 1:
        ans += a - 1
        mn = 2
    else:
        if mn == a:
            mn += 1
        else:
            ans += (a - 1) // mn
print(ans)            
