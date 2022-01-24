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
a, b = map(int, input().split())
a -= 1
b -= 1
ch = list(S)
ch[a], ch[b] = ch[b], ch[a]
print(''.join(ch))
