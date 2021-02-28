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
ans = int(1e10)
for n in range(N):
    a, p, x = map(int, input().split())
    remain = x - a
    if remain > 0:
        ans = min(ans, p)
if ans == int(1e10):
    print(-1)
else:
    print(ans)

    

