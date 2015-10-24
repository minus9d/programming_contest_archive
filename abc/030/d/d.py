#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,a = map(int,input().split())
k = int(input())
Bs = list(map(int,input().split()))

order = [a]
seen = {a:0}
nxt = a
while True:
    nxt = Bs[nxt - 1]
    if nxt in seen:
        repStartIdx = seen[nxt]
        repEndIdx = len(seen)-1
        break
    else:
        seen[nxt] = len(seen)
        order.append(nxt)

# print(seen)
# print(order)

if len(order) > k+1:
    print(order[k])
else:
    idx = (k - repStartIdx) % (repEndIdx - repStartIdx + 1) + repStartIdx
    print(order[idx])
