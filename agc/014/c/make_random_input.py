#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import random
H = 800
W = 800
K = 40
print(H, W, K)
for h in range(H):
    for w in range(W):
        if h == H // 2 and w == W // 2:
            char = 'S'
        elif random.random() > 0.5:
            char = '#'
        else:
            char = '.'
        print(char, end="")
    print()

    
