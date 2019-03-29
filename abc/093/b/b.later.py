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

A, B, K = map(int, input().split())
s = set()
for v in range(A, min(B + 1, A + K)):
    s.add(v)
for v in range(max(A, B - K + 1), B + 1):
    s.add(v)
for v in sorted(s):
    print(v)
