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
B = map(int, input().split())

ans = 0
for i, b in enumerate(B):
    if i == 0:
        ans += b
    else:
        ans += min(b, prev)
    prev = b
ans += prev
print(ans)
