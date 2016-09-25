#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
As = list(map(int,input().split()))

ans = 0
for i,a in enumerate(As):
    if i == As[a-1]-1:
        ans += 1
print(ans//2)

