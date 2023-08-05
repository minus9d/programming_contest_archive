#!/bin/env python

N = int(input())
P = list(map(int, input().split()))

if N == 1:
    print(0)
else:
    mx = max(P[1:])
    if P[0] > mx:
        print(0)
    else:
        print(mx + 1 - P[0])
