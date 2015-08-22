#!/usr/bin/env python3
# -*- coding: utf-8 -*-

nums = list(map(int,input().split()))
nums.sort()
if nums[0] == nums[1]:
    print(nums[2])
else:
    print(nums[0])
