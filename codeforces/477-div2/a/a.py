#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import random
import re
import string

N, S = map(int, input().split())


hms = []
for n in range(N):
    h, m = map(int, input().split())
    hms.append((h, m))

def get_time(cur_h, cur_m, h, m):
    ret = (h - cur_h) * 60
    ret += m - cur_m
    return ret

def add_time(cur_h, cur_m, h, m):
    ret_h = cur_h + h
    ret_m = cur_m + m
    while ret_m >= 60:
        ret_h += 1
        ret_m -= 60
    return ret_h, ret_m

cur_h = 0
cur_m = 0
for n in range(N):
    h, m = hms[n]
    time = get_time(cur_h, cur_m, h, m)
#    print("time, cur_h, cur_m", time, cur_h, cur_m)

    if n == 0 and time >= S + 1:
        print("0 0")
        break
    elif time >= S * 2 + 1:
        ans = add_time(cur_h, cur_m, 0, S)
        print(*ans)
        break
    else:
        cur_h, cur_m = add_time(h, m, 0, 1)
else:
    ans = add_time(cur_h, cur_m, 0, S)
    print(*ans)
