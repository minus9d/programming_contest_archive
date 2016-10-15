#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N=int(input())

def gcd(a,b):
    while b > 0:
        a, b = b, a % b
    return a
    
def lcm(a, b):
    return a * b / gcd(a, b)

def func1(x, xi):
    if x % xi == 0:
        return x
    else:
        return xi * (x // xi) + xi

for i in range(N):
    ti,ai = map(int,input().split())
    if i == 0:
        t,a = ti,ai
    else:
        t,a = func1(t, ti),func1(a, ai)

        # a is short
        if ti / ai < t / a:
            a = t // ti * ai
        else:
            t = a // ai * ti

    # print("t,a=",t,a)
print(a+t)

