#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# 相手の手に関わらず gpgpgp.. と出すと最適

S = input()
T = "gp" * len(S)
ans = 0
for s,t in zip(S,T):
    if t == 'g' and s == 'p':
        ans -= 1
    elif t == 'p' and s == 'g':
        ans += 1
print(ans)
