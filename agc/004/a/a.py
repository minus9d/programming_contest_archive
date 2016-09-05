#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def func(a,b,c):
    return (a - 2 * (a//2)) * b * c

a,b,c = map(int,input().split())
print(min(func(a,b,c),func(b,c,a),func(c,a,b)))
