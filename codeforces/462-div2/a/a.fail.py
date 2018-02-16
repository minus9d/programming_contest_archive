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

N, M = map(int, input().split())
A = list(map(int, input().split()))
B = list(map(int, input().split()))
A.sort()
B.sort()

cand1 = max(A[-2] * B[-1], A[0] * B[0])
cand2 = max(A[1] * B[0], A[-1] * B[-1])
print(min(cand1, cand2))
