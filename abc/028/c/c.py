#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools

nums = list(map(int,input().split()))

possible = set()
for comb in itertools.combinations(nums,3):
    possible.add(sum(comb))

l = list(possible)
l.sort()
print(l[-3])
    
