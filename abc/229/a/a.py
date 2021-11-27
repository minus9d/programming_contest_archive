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


S1 = input()
S2 = input()
num = (S1 + S2).count('#')
if num == 2:
    if (S1 == '.#' and S2 == '#.') or (S2 == '.#' and S1 == '#.'):
        print('No')
    else:
        print('Yes')
else:
    print('Yes')
