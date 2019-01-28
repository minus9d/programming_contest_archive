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
A = input()
B = input()
C = input()

ans = 0
for a, b, c in zip(A, B, C):
    s = set([a, b, c])
    ans += len(s) - 1
print(ans)

  
