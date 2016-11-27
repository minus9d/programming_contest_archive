#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import re
s = input()
t = []
for ch in s:
    if ch == 'C' or ch == 'F':
        t.append(ch)
t = "".join(t)
if "CF" in t:
    print("Yes")
else:
    print("No")

