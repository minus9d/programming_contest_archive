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

N, K = map(int, input().split())

ans = 0
if K % 2 == 0:
    num = 0
    for i in range(1, N+1):
        if i % K == K // 2:
            num += 1
    ans += num ** 3

num = 0
for i in range(1, N+1):
    if i % K == 0:
        num += 1
ans += num ** 3

print(ans)


