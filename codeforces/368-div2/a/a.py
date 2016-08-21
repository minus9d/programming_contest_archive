#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N,M = map(int,input().split())

chars = set()
for n in range(N):
    chars |= set(input().split())
if 'C' in chars or 'M' in chars or 'Y' in chars:
    print("#Color")
else:
    print("#Black&White")
