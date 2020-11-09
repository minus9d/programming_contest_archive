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
As = list(map(int, input().split()))

mx = 0
for k in range(2, 1001):
    cnt = 0
    for a in As:
        cnt += a % k == 0
    if cnt > mx:
        ans = k
        mx = cnt
print(ans)


