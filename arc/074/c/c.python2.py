#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# import array
# from bisect import *
# from collections import *
# import fractions
# import heapq 
# from itertools import *
# import math
# import re
# import string

def max_minus_min(areas):
    # print("areas", areas)
    return max(areas) - min(areas)

def solve2(h, w):
    area1 = h * (w // 2)
    area2 = h * w - area1
    return [area1, area2]

def solve(h, w):
    w_div_3 = w // 3;
    ans = 1e9
    for w2 in range(w_div_3, w_div_3 + 2):
        area1 = w2 * h
        ans = min(ans, max_minus_min([area1] + solve2(h, w - w2)))
        ans = min(ans, max_minus_min([area1] + solve2(w - w2, h)))
    return ans

H, W = map(int, raw_input().split())
print(min(solve(H,W), solve(W,H)))
