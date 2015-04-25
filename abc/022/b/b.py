#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
d = set()
ans = 0
for n in range(N):
    a = int(input())
    if a in d:
        ans += 1
    else:
      d.add(a)
print(ans)
