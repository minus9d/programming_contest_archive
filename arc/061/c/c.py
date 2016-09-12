#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools

S = input()
signs = [['+',''] for _ in range(len(S)-1)]

ans = 0
for comb in itertools.product(*signs):
    expr = ''
    for i in range(len(S)-1):
        expr += (S[i] + comb[i])
    expr += S[-1]
    ans += eval(expr)
print(ans)        
