#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = 1000
M = 1000
Q = 100000
print(N,M,Q)

import random

type = 0
for q in range(Q):
    if type == 0 or type == 1:
        print(type+1, random.randint(1,N), random.randint(1,M))
    elif type == 2:
        print(type+1, random.randint(1,N))
    else:
        print(type+1, random.randint(0,q))
    type = (type + 1) % 4


