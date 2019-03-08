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
S = input()

ans = 0
for i in range(N):
    ans = max(ans, len(set(S[:i]) & set(S[i:])))
print(ans)
