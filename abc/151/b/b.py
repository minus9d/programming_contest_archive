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

N, K, M = map(int, input().split())
As = list(map(int, input().split()))

need = N * M
curr = sum(As)
remain = need - curr
# print(need, curr, remain)

if remain <= 0:
    print(0)
elif remain > K:
    print(-1)
else:
    print(remain)



