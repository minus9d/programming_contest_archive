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
B = int(input())
s = set([A, B])
for i in range(1, 4):
    if i not in s:
        print(i)


