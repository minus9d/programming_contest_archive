#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# reference:
#   http://arc050.contest.atcoder.jp/submissions/683977
#   http://arc050.contest.atcoder.jp/data/arc/050/review.pdf
#   http://pekempey.hatenablog.com/entry/2016/04/03/164556

def gcd(x,y):
    return gcd(y%x, x) if x else y

def power(x,n,mod):
    if n == 0:
        return 1
    y = power(x, n//2, mod)
    y = y * y % mod
    if n % 2 == 1:
        y = y * x % mod
    return y
    
def func(ten, n, mod):
    #print("func({},{},{})".format(ten,n,mod))
    if n == 0:
        return 0
    if (n % 2 == 1):
        return (func(ten, n-1, mod) * ten + 1) % mod
    return func(ten, n//2, mod) * (power(ten, n//2, mod) + 1) % mod

for n in range(1, 10):
    mod = 100000
    print("func({},{},{}) = {}", 10,n,mod,func(10,n,mod))
sys.exit()

A,B,M = [int(x) for x in input().split()]
d = gcd(A,B) # d = gcd(A, B)

# lcm(x,y) = (one(A)*one(B))/one(D)
#          = one(A) * (one(B)/one(D))
#          

x = func(10%M, A, M)
y = func(power(10, d, M), B//d, M)
print(x*y%M)
