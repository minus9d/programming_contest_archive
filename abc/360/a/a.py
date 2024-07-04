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


S = input()
r = S.find('R')
m = S.find('M')
if r < m:
    print('Yes')
else:
    print('No')

