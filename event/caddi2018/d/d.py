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
As = []
for n in range(N):
    As.append(int(input()))

first_win = False
for a in As:
    if a % 2 == 1:
        first_win = True
if first_win:
    print("first")
else:
    print("second")
