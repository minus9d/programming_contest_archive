#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math
log = math.log

A,K = map(int,input().split())
target = 2000000000000

if K == 0:
    print(target - A)
else:
    day = 0
    while A < target:
        A = A * (K + 1) + 1
        day += 1
    print(day)
