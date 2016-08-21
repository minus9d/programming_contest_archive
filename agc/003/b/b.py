#!/usr/bin/env python3
# -*- coding: utf-8 -*-
N = int(input())
ans = 0
carry = 0
for n in range(N):
    a = int(input())
    if carry and a > 0:
        ans += 1
        a -= 1
    ans += a // 2
    if a % 2 == 1:
        carry = 1
    else:
        carry = 0
print(ans)
