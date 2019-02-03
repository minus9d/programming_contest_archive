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


def solve(N, M, Xs):
    if M <= N:
        return 0

    diffs = []
    for i in range(M - 1):
        diffs.append(Xs[i+1] - Xs[i])
    diffs.sort()

    return sum(diffs[:M - N])


N, M = map(int, input().split())
Xs = sorted(list(map(int, input().split())))
print(solve(N, M, Xs))
