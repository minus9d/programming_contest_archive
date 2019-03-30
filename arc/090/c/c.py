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
A1 = list(map(int, input().split()))
A2 = list(map(int, input().split()))

ans = A1[0] + sum(A2)
cur = ans
for i in range(N-1):
    cur -= A2[i]
    cur += A1[i+1]
    ans = max(ans, cur)
print(ans)

    
