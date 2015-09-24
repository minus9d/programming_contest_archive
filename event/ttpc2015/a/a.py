#!/usr/bin/env python3
# -*- coding: utf-8 -*-
 
s = input()
a = s[2]
m = ""
if a == 'B':
    m = "Bachelor"
elif a == 'M':
    m = "Master"
else:
    m = "Doctor"
 
print(m, s[:2])
