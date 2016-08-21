#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
nums = [0] * N
for pos in range(N):
    nums[pos] = int(input())
snums = sorted(nums[:])
rank = {}
for i,e in enumerate(snums):
    rank[e] = i+1

rev = 0
for i,e in enumerate(nums):
    if (i + rank[e]) % 2 == 0:
        rev += 1
print(rev // 2)
