#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import fractions
import sys

MOD = 1000000007
N = int(input())
Ls = []
odd = False
for n in range(N):
    t = int(input())
    Ls.append(t)
    if t%2: odd = True
Ls.sort()

mn = Ls[0]
for i in range(1,N):
    if i == 1:
        n = Ls[i]-mn
    else:
        n = fractions.gcd(n, Ls[i]-mn)
print(pow(2, (mn+(n+1)//2), MOD))
        
