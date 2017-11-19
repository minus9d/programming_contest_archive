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

nums = list(map(int, list(input())))

cand = [(nums[0], [str(nums[0])])]

for num in nums[1:]:
    new_cand = []
    for s, signs in cand:
        new_cand.append((s + num, signs + ['+', str(num)]))
        new_cand.append((s - num, signs + ['-', str(num)]))
    cand = new_cand

for num, signs in cand:
    if num == 7:
        print(''.join(signs) + '=7')
        break
