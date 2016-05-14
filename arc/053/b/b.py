#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from collections import Counter

S = input()
c = Counter(S)

palin_num = sum([1 for x in c.values() if x % 2])
if palin_num == 0:
    print(len(S))
else:
    even_num = len(S) - palin_num
    print(1 + ((even_num // 2) // palin_num) * 2)
