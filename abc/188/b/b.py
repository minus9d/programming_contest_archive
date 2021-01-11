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
As = list(map(int, input().split()))
Bs = list(map(int, input().split()))

t = 0
for a, b in zip(As, Bs):
    t += a * b
if t == 0:
    print('Yes')
else:
    print('No')



