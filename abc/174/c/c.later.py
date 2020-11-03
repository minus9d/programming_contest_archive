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

K = int(input())

val = 7
for n in range(1000010):
    val %= K
    if val == 0:
        print(n + 1)
        sys.exit(0)
    val *= 10
    val += 7

print(-1)


