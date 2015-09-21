#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,B,C = map(int,input().split())
As = list(map(int,input().split()))

remain = C
ans = 0
for n in range(N):
    r = min(remain, B)
    remain -= r
    ans += As[N-n-1] * r
print(ans)
