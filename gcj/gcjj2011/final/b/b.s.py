#!/usr/bin/env python3
# -*- coding: utf-8 -*-

T = int(input())
for testcase in range(T):
    A,B,C = [int(x) for x in input().split()]

    x = A
    for b in range(B):
        if b == 0:
            x = pow(x,x)
        else:
            x = pow(x,x,C)
    x %= C
    print("Case #{}: {}".format(testcase+1, x))
