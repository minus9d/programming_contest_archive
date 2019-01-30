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
while True:
    n_str = sorted(str(N))
    if n_str[0] == n_str[-1]:
        break
    N += 1
print(N)
