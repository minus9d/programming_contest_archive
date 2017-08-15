#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N, K = map(int,input().split())
As = list(map(int,input().split()))
As.sort()
print(sum(As[:K]) + (K-1) * K // 2)

