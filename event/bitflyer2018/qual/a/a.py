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

n = A
while n % B != 0:
    n -= 1
print(n)

