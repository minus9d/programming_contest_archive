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
import sys


sys.setrecursionlimit(10 ** 9)


N = int(input())
A = list(map(int, input().split()))
W = list(map(int, input().split()))


box = defaultdict(list);
for a, w in zip(A, W):
    a -= 1
    box[a].append(w)

# for k, v in box.items():
#     print(k, v)

ans = 0
for b in box.values():
    b.sort(reverse=True)
    ans += sum(b[1:])
print(ans)


    


