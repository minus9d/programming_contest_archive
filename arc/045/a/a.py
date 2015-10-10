#!/usr/bin/env python3
# -*- coding: utf-8 -*-

S = input()
table = (("Left", "<"), ("Right", ">"), ("AtCoder", "A"))
for t in table:
    S = S.replace(t[0], t[1])
print(S)
