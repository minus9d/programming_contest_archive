#!/usr/bin/env python3
# -*- coding: utf-8 -*-

A,B,K,L = map(int,input().split())
if L * A < B:
    print(K * A)
else:
    if K % L == 0:
        print((K // L) * B)
    else:
        num = (K // L)
        v1 = num * B + (K - (num * L)) * A
        v2 = (num + 1) * B
        print(min(v1,v2))
