#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import defaultdict

S = input()
S = sorted(S)
S = list(map(ord, S))

ans = 0
while len(S) > 0:
    mn = S[0]
    S.remove(mn)
    nxt = mn + 1
    succ = 1
    while True:
        if nxt in S:
            S.remove(nxt)
            succ += 1
            nxt += 1
        else:
            break
    ans += min(3, succ)
print(ans)
