#!/usr/bin/env python
# -*- coding: utf-8 -*-

MOD = 1000000007

def nCr(n,k):
    if (k > n or n <= 0 or k <= 0):
        return 0

    num=1
    for i in range(0,n):
        num *= (i+1)
    for i in range(0,k):
        num //= (i+1)
    for i in range(0,n-k):
        num //= (i+1)
    return num

(R,C)=map(int,input().split())
(X,Y)=map(int,input().split())
(D,L)=map(int,input().split())

ret=(R-X+1) *(C-Y+1) * (nCr(X*Y, D)-2*nCr((X-1)*Y, D)-2*nCr(X*(Y-1), D) + ) * nCr(D+L, D)

print(ret%MOD)

