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


sys.setrecursionlimit(10 ** 9)

A = list(map(int, input().split()))
A.sort()

if A[0] == A[1] or A[1] == A[2]:
    print('Yes')
else:
    print('No')

