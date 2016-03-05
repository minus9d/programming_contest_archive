#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import fractions
import functools

MOD = 1000000007
N = int(input())

Ls = []
for n in range(N):
    t = int(input())
    Ls.append(t)

mn = min(Ls)


# Ls = [3, 7, 11, 15]のとき、
# これらからもっとも短い長さ3を引いた[0, 4, 8, 12]のgcdをもとめる
# gcd(0, a) = aとなるので、0は無視できる
gcded = functools.reduce(fractions.gcd, [x - mn for x in Ls])

print(pow(2, (mn + (gcded+1)//2), MOD))
        
