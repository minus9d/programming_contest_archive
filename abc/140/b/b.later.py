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
As = list(map(int, input().split()))
Bs = list(map(int, input().split()))
Cs = list(map(int, input().split()))

ans = sum(Bs)
for n in range(N-1):
    if As[n+1] - As[n] == 1:
        ans += Cs[As[n] - 1]
print(ans)

