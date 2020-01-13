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
As = list(map(int, input().split()))
As.sort()

arr = []
for i in range(K - 1, N):
    arr.append(As[i] - As[0])
print(arr)

arr_sum = sum(arr)

