#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import itertools

S = input()
N = int(input())

for i, c in enumerate(itertools.product(S, repeat=2)):
    if i + 1 == N:
        print("".join(c))
