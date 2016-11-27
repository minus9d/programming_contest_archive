#!/usr/bin/env python3
# -*- coding: utf-8 -*-
s = input()
gt = "CODEFESTIVAL2016"

ans = 0
for i in range(len(gt)):
    if s[i] != gt[i]:
        ans += 1
print(ans)
