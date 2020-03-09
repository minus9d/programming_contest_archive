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

A, B, M = map(int, input().split())
As = list(map(int, input().split()))
Bs = list(map(int, input().split()))

ans = min(As) + min(Bs)
for m in range(M):
    x, y, c = map(int, input().split())
    tmp = As[x - 1] + Bs[y - 1] - c
    ans = min(ans, tmp)
print(ans)

