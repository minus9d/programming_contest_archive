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

X, Y = map(int, input().split())
n = X
ans = 0
while n <= Y:
    ans += 1
    n *= 2
print(ans)
