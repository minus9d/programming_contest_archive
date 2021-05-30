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

N, K = map(int, input().split())

s = 0
for n in range(1, N + 1):
    for k in range(1, K + 1):
        s += n * 100 + k
print(s)


