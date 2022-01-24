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


N, M  = map(int, input().split())
Ss = list(input().split())
Ts = list(input().split())
seen = set(Ts)

for s in Ss:
    if s in seen:
        print('Yes')
    else:
        print('No')





