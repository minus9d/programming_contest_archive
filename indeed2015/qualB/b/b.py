#!/usr/bin/env python3
# -*- coding: utf-8 -*-

def solve():
    s = input()
    t = input()
    for i in range(len(s)):
        if s == t:
            return i
        s = s[-1] + s[:-1]
    return -1
print(solve())

            

    
