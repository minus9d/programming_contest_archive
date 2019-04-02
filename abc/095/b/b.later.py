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

N, X = map(int, input().split())
Ms = list()
for n in range(N):
    Ms.append(int(input()))
ans = N
X -= sum(Ms)
ans += X // min(Ms)
print(ans)
