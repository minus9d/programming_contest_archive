#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import math

N = int(input())
EPS = 1e-7

def dist2(x1,y1,x2,y2):
    return (x2-x1)**2 + (y2-y1)**2

def dist(x1,y1,x2,y2,x3,y3):
    d1 = dist2(x1,y1,x2,y2)
    d2 = dist2(x1,y1,x3,y3)
    d3 = dist2(x3,y3,x2,y2)
    d = min(d1,d2,d3)
    return math.sqrt(d)

def f1(w,h,p1y):
    # P0(0,0)
    # P1(w,y)
    # P2(0,p2y)

    lo = 0
    hi = h
    while(abs(hi - lo) > EPS):
        width = hi - lo
        ml = lo + hi / 3.0
        mr = lo + 2.0 * hi / 3.0
        if dist(0,0,w,p1y,0,ml) >= dist(0,0,w,p1y,0,mr):
            hi = mr
        else:
            lo = ml
    ans = dist(0,0,w,p1y,0,(lo+hi)/2)
    print("ok f1")
    return ans

def f2(w,h,p1y):
    # P0(0,0)
    # P1(w,y)
    # P2(p2x,h)

    lo = 0
    hi = w
    while(abs(hi - lo) > EPS):
        width = hi - lo
        ml = lo + hi / 3.0
        mr = lo + 2.0 * hi / 3.0
        if dist(0,0,w,p1y,ml,h) >= dist(0,0,w,p1y,mr,h):
            hi = mr
        else:
            lo = ml
        print("lo,hi=",lo,hi)
        print("ml,mr=",ml,mr)
    ans = dist(0,0,w,p1y,(lo+hi)/2,h)
    return ans

def f(w,h,p1y):
    # P0(0,0)
    # P1(w,y)
    # P2(0,p2y) or P2(p2x,h)

    ans1 = f1(w,h,p1y)
    # ans2 = f2(w,h,p1y)
    return ans1

    return max(ans1,ans2)

for _ in range(N):
    t1,t2 = map(int,input().split())
    # w >= h
    w = max(t1,t2)
    h = min(t1,t2)

    ans = math.hypot(h, w/2.0)
    if w < ans:
        lo = 0
        hi = h
        while(hi - lo > EPS):
                width = hi - lo
                ml = lo + hi / 3.0
                mr = lo + 2.0 * hi / 3.0
                if (f(w,h,ml) >= f(w,h,mr)):
                    hi = mr
                else:
                    lo = ml
                print("ok lo,hi=",lo,hi)
                ans = f(w,h,(hi+lo)/2.0)
                
        print("lo,hi=",lo,hi)
        
    print("{0:.12f}".format(ans))
