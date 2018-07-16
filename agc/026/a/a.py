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
As = map(int, input().split())

prev = -1
cnt = 0
ans = 0
for a in As:
    if a == prev:
        cnt += 1
    else:
        ans += cnt // 2
        cnt = 1
    prev = a
ans += cnt // 2
print(ans)


