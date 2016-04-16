#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
x1,y1,r = [int(x) for x in input().split()]
x2,y2,x3,y3 = [int(x) for x in input().split()]

def point_is_inside_circle(x,y):
    dist2 = (x-x1)**2 + (y-y1)**2
    return dist2 <= r**2

def point_is_inside_rect(x,y):
    return x2 <= x <= x3 and y2 <= y <= y3

def circle_is_inside_rect():
    return point_is_inside_rect(x1-r,y1) \
        and point_is_inside_rect(x1+r,y1) \
        and point_is_inside_rect(x1,y1+r) \
        and point_is_inside_rect(x1,y1-r)

def rect_is_inside_circle():
    return point_is_inside_circle(x2,y2) \
        and point_is_inside_circle(x2,y3) \
        and point_is_inside_circle(x3,y2) \
        and point_is_inside_circle(x3,y3)

if rect_is_inside_circle():
    print("YES")
    print("NO")
elif circle_is_inside_rect():
    print("NO")
    print("YES")
else:
    print("YES")
    print("YES")
