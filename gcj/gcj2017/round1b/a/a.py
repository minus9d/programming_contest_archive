#!/usr/bin/env python3
# -*- coding: utf-8 -*-

T = int(input())
for testcase in range(T):
    D, N = map(int, input().split())
    t_max = 0
    for n in range(N):
        k, s = map(int, input().split())
        t = (D - k) / s
        t_max = max(t, t_max)
    print("Case #{}: ".format(testcase+1), end="")
    print("{:.10f}".format(D / t_max))
