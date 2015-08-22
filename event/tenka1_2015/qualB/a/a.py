#!/usr/bin/env python3
# -*- coding: utf-8 -*-

a = [100,100,200]
for i in range(17):
    a.append( sum(a[-3:]) )
print(a[-1])

