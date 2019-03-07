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

A, B, K = map(int, input().split())
nums = []
for i in range(min(A, B), 0, -1):
    if A % i == B % i == 0:
        nums.append(i)
print(nums[K - 1])

