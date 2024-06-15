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
import numpy as np

sys.setrecursionlimit(10 ** 9)


def make_carpet(level):
  if level == 0:
    return np.array([[0]], dtype=np.int8)
  else:
    ret = np.zeros((3 ** level, 3 ** level), dtype=np.int8)
    pre = make_carpet(level - 1)
    pre_size = 3 ** (level - 1)
    for y in range(3):
      for x in range(3):
        if x == y == 1:
          pattern = np.ones((pre_size, pre_size), dtype=np.int8)
        else:
          pattern = pre
        ret[y * pre_size : (y + 1) * pre_size, x * pre_size : (x + 1) * pre_size] = pattern
  
    return ret

N = int(input())
ret = make_carpet(N)

for row in ret:
  for e in row:
    if e == 0:
      print('#', end='')
    else:
      print('.', end='')
  print()

