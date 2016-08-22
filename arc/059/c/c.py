#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
As = list(map(int,input().split()))

mn_cost = 1e10
for v in range(-100,101):
    cost = sum((v - a) ** 2 for a in As)
    if cost < mn_cost:
        mn_cost = cost
print(mn_cost)
