#!/usr/bin/env python3
# -*- coding: utf-8 -*-

N = int(input())
nums = list(map(int,input().split()))
s = sum(nums)
if s // N * N != s:
    print(-1)
else:
    ans = 0
    target = s // N
    x = 0
    y = 0
    for n in range(N):
        x += nums[n]
        y += 1
        if x == target * y:
            x,y = 0,0
            continue
        else:
            ans += 1
    print(ans)
