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
Xs = list(map(int, input().split()))

Ys = Xs[:]
Ys.sort()

a = Ys[N//2 - 1]
b = Ys[N//2]

for x in Xs:
    if x <= a:
        print(b)
    else:
        print(a)
