#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import *
S = input()

seen = set()
dq = deque()

ok = False
seen.add(0)
while len(seen) > 0:
    pos = sorted(list(seen))[0]
    seen.remove(pos)
    if pos == len(S):
        ok = True
        break

    part = S[pos:]
    if part.startswith('dream'):
        seen.add(pos + 5)
    if part.startswith('dreamer'):
        seen.add(pos + 7)
    if part.startswith('erase'):
        seen.add(pos + 5)
    if part.startswith('eraser'):
        seen.add(pos + 6)
if ok:
    print('YES')
else:
    print('NO')

    
    
        
        
