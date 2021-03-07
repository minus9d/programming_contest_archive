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

N = int(input())
A = []
B = []
for n in range(N):
    a, b = map(int, input().split())
    A.append(a)
    B.append(b)

ans = 1e10
for i in range(N):
    for j in range(N):
        if i == j:
            ans = min(ans, A[i] + B[i])
        else:
            ans = min(ans, max(A[i],B[j]))
print(ans)

    

