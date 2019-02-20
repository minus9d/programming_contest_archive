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

def gcd(a, b):
    if a % b == 0:
        return b
    else:
        return gcd(b, a % b)

N = int(input())
As = map(int, input().split())

ans = None
for a in As:
    if ans is None:
        ans = a
    else:
        ans = gcd(ans, a)
print(ans)
