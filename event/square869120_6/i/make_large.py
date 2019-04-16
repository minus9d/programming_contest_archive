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

H, W = map(int, sys.argv[1:])
print(H, W)
for h in range(H):
    nums = [random.randint(1, 9) for _ in range(W)]
    print(*nums)
       

