#!/usr/bin/env python3
# -*- coding: utf-8 -*-

terms = input().split('+')
ans = 0
for term in terms:
    nums = term.split('*')
    ans += not "0" in nums
print(ans)

