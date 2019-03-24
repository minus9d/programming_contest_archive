#!/usr/bin/env python3
# -*- coding: utf-8 -*-

S = input()

len = 0
ans = 0
for ch in S:
    if ch in 'ACGT':
        len += 1
        ans = max(ans, len)
    else:
        len = 0
print(ans)
        
