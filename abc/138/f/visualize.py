#!/usr/bin/env python3
# -*- coding: utf-8 -*-

for y in range(1, 101):
    for x in range(1, 101):
        if (y % x == y ^ x):
            print("o", end="")
        else:
            print(".", end="")
    print()

