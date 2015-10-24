#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve(s):
    idx = 0
    ret = 0
    while True:
        i1 = s.find("kyoto", idx)
        i2 = s.find("tokyo", idx)
        # print(i1,i2)
        if i1 == i2 == -1:
            return ret
        else:
            if i1 == -1: idx = i2
            elif i2 == -1: idx = i1
            else: idx = min(i1,i2)
            idx += 5
            ret += 1


N = int(input())
for _ in range(N):
    S = input()
    print(solve(S))
