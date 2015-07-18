#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

N = int(input())
Rs = []
for n in range(N):
    Rs.append(int(input()))
Rs = reversed(sorted(Rs))

area = 0
for i, R in enumerate(Rs):
    if i % 2 == 0:
        area += pow(R, 2)
    else:
        area -= pow(R, 2)
area *= math.pi
print(area)

