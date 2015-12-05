#!/usr/bin/env python3
# -*- coding: utf-8 -*-
a1,a2 = map(int,input().split())
b1,b2 = map(int,input().split())
c = int(input())

cand = set()
if a1 == c or a2 == c:
    cand.update([b1,b2])
if b1 == c or b2 == c:
    cand.update([a1,a2])

print(len(cand))
candSorted = sorted(list(cand))
for c in candSorted:
    print(c)


