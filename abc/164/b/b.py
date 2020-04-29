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

A, B, C, D = map(int, input().split())

while True:
    C -= B
    if C <= 0:
        print('Yes')
        sys.exit(0)
    A -= D
    if A <= 0:
        print('No')
        sys.exit(0)

