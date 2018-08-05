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

A = int(input())
S = input()
flag = False
if A == 0:
    flag = True
for ch in S:
    if ch == '+':
        A += 1
    else:
        A -= 1
    if A == 0:
        flag = True
if flag:
    print('Yes')
else:
    print('No')

