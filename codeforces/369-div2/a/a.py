#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())

ok = False
lines = []
for n in range(N):
    line = input()
    if "OO" in line and not ok:
        line = line.replace("OO", "++", 1)
        ok = True
    lines.append(line)
if ok:
    print ("YES")
    print("\n".join(lines))
else:
    print ("NO")

