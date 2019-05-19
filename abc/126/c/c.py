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

N, K = map(int, input().split())

pred_sum = 0.0
for n in range(1, N + 1):
    n2 = n
    cnt = 0
    while n2 < K:
        n2 *= 2
        cnt += 1
    pred_sum += 0.5 ** cnt
print("{:.15f}".format(pred_sum / N))
