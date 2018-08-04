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

f, s = map(int, input().split())

cnt = 0
while f >= 2 and s >= 1:
    cnt += 1
    f -= 2
    s -= 1
if cnt % 2:
    print('O')
else:
    print('K')
