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

N, M, X = map(int, input().split())

As = list(map(int, input().split()))
A_set = set(As)

def count(f, t, A_set):
    ret = 0
    for i in range(f, t + 1):
        ret += i in A_set
    return ret

ans1 = count(0, X, A_set)
ans2 = count(X, N, A_set)
print(min(ans1, ans2))




