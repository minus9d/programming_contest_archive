#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
S = input()

words = S.split()

ret = []
stack = []
for w in words:
    if w == "not":
        stack.append(w)
    else:
        if len(stack) % 2:
            ret.append("not")
        ret.append(w)
        stack = []
ret += stack
print(" ".join(ret))
