#!/usr/bin/env python3
# -*- coding: utf-8 -*-

X = input()
S = ""
for ch in X:
    if ch == 'S':
        S += ch
    else:
        if len(S) > 0 and S[-1] == 'S':
            S = S[:-1]
        else:
            S += ch
print(len(S))
