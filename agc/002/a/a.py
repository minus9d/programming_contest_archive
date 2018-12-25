#!/usr/bin/env python3
# -*- coding: utf-8 -*-

a,b = map(int,input().split())
if a > 0:
    print("Positive")
elif a <= 0 <= b:
    print("Zero")
else:
    num = abs(a) - abs(b) + 1
    if num % 2:
        print("Negative")
    else:
        print("Positive")
