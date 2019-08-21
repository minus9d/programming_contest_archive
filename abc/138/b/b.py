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
As = list(map(int, input().split()))

mul = 1
for a in As:
    mul *= a

s = 0
for a in As:
    s += mul // a

print("{:.15f}".format(mul / s))

