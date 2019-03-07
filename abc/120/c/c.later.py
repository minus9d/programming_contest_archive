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

S = input()
stack = []
ans = 0
for ch in S:
    if len(stack) == 0 or stack[-1] == ch:
        stack.append(ch)
    else:
        ans += 2
        # stack = stack[:-1]  # 遅い??
        del stack[-1]
print(ans)


