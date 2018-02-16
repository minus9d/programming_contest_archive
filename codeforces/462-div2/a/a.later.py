#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# 
# 本番では、数列aが0以上、数列bが0以下のみからなる場合を考慮しておらずWA
# このように全探索すべきだった
#

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

N, M = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))
A.sort()
B.sort()

ans = 1e20
for i in range(N):
    A2 = A[:i] + A[i+1:]
    local_ans = -1e20
    for a in A2:
        for b in B:
            local_ans = max(local_ans, a * b)
    # print(A2, B)
    # print("local_ans:", local_ans)
    ans = min(ans, local_ans)
print(ans)
