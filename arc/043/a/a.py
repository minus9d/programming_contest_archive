#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,A,B = map(int,input().split())
vals = []
for _ in range(N):
    vals.append(int(input()))
vals.sort()

if vals[0] == vals[-1]:
    if B != 0:
        print(-1)
    else:
        # P is any
        P = 1.0
        Q = float(A) - 1.0 / N * sum(vals)
        print(P, Q)
else:
    P = float(B) / (vals[-1] - vals[0])
    Q = float(A) - P / N * sum(vals)
    print(P, Q)
