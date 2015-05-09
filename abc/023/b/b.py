#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N=int(input())
S=input()

seen = {}
s = 'b'
seen[s] = 0
for i in range(1, 101):
    if i % 3 == 1:
        s = 'a' + s + 'c'
    elif i % 3 == 2:
        s = 'c' + s + 'a'
    else:
        s = 'b' + s + 'b'
    seen[s] = i

if S in seen:
    print(seen[S])
else:
    print(-1)


