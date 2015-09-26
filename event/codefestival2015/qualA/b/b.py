#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
As = list(map(int,input().split()))

ans = 0
for i, A in enumerate(As):
   ans += A * pow(2, N - (i + 1))
print(ans)
 
