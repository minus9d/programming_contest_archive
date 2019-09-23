#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
from heapq import *
from itertools import *
import math
import random
import re
import string
import sys

N, M = map(int, input().split())
As = list(map(int, input().split()))

h = []
for a in As:
    heappush(h, -a)

for m in range(M):
    val = heappop(h)
    heappush(h, -((-val) // 2))

print(-sum(h))

