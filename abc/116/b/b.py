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

s = int(input())
i = 1
As = set()
As.add(s)
prev = s
while True:
    i += 1
    if prev % 2:
        s = 3 * prev + 1
    else:
        s = prev // 2
    if s in As:
        print(i)
        break
    As.add(s)
    prev = s


