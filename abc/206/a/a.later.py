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

N = int(input())
val = N * 108 // 100
if val < 206:
    print('Yay!')
elif val == 206:
    print('so-so')
else:
    print(':(')
