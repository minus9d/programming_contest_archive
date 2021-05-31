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

S = input()
S = S[::-1]

T = []
for ch in S:
    if ch == '6':
        T.append('9')
    elif ch == '9':
        T.append('6')
    else:
        T.append(ch)
print(''.join(T))

