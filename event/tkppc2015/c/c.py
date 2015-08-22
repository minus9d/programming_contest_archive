#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N, M = map(int, input().split())
S = int(input())
    
event = []
for _ in range(N):
    T, K = map(int, input().split())
    event.append( (T,K) )

ans = 0
emo = 0
t = 0
event.sort()
for (T,K) in event:
    if emo >= M:
        ans += T - t
    emo += K
    t = T
if emo >= M:
    ans += (S - t)
    
print(ans)

