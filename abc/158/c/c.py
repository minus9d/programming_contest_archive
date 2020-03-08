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

A, B = map(int, input().split())
for i in range(1, 1100):
    a = i * 8 // 100
    b = i * 10 // 100
    if a == A and b == B:
        print(i)
        sys.exit(0)
print(-1)
