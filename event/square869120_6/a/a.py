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

N, T = map(int, input().split())
As = list(map(int, input().split()))

time = 0
ans = 0
for a in As:
    if time + a <= 0:
        time += a
    else:
        while time + a > 0:
            time -= T
            ans += 1
        time += a

print(ans)

