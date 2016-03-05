#!/usr/bin/env python3
# -*- coding: utf-8 -*-

a,b = [int(x) for x in input().split()]
a,b = [x if x > 0 else x + 1 for x in [a,b]]
print(b-a)
