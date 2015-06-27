#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,A,B = map(int,input().split())

loc = 0
for n in range(N):
    s,d = input().split()
    d = int(d)
    dis = min(max(d, A), B)
    if s == 'East':
        loc -= dis
    else:
        loc += dis

if loc == 0:
    print(0)
elif loc > 0:
    print('West ' + str(loc))
else:
    print('East ' + str(abs(loc)))
