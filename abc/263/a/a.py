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


As = list(map(int, input().split()))

def judge(As):
    s = Counter(As)
    if len(s) != 2:
        return False
    else:
        for k, v in s.items():
            if v == 2 or v == 3:
                return True
            else:
                return False
if judge(As):
    print('Yes')
else:
    print('No')

