#!/usr/bin/env python3
# -*- coding: utf-8 -*-
n = int(input())
s = input()
for n in range(100,0,-1):
    filler = "o" + "go" * n
    s = s.replace(filler, "***")
print(s)
    
