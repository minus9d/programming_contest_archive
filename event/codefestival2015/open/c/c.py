#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
As = map(int,input().split())
X = int(input())

cnt = 0
for a in As:
    if X > a:
        cnt += 1
    else:
        break
print(cnt+1)

