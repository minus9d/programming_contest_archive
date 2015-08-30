#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N,K = map(int,input().split())
n1 = (K-1) * (N-K) * 6
n2 = (N-1) * 3
n3 = 1
p = (n1+n2+n3)/(N*N*N)
print("{0:.16f}".format(p))

