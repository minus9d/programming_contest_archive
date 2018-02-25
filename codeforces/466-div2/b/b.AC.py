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

N = int(input())
K = int(input())
A = int(input())
B = int(input())

if K == 1:
    print ((N - 1) * A)
else:
    ans = 0
    x = N
    while x > 1:
        if x < K:
            ans += (x - 1) * A
            break
        elif x % K != 0:
            new_x = (x // K) * K
            ans += (x - new_x) * A
            x = new_x
        else:
            new_x = x // K
            cost1 = B
            cost2 = (x - new_x) * A
            ans += min(cost1, cost2)
            x = new_x
    #    print("x, ans = ", x, ans)
    print(ans)
