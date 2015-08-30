#!/usr/bin/env python3
# -*- coding: utf-8 -*-

S = input()
chars = ['A', 'B', 'C', 'D', 'E', 'F']
ret = []
for ch in chars:
    ret.append( S.count(ch) )

print(" ".join(map(str,ret)))
