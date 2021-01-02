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

def S(n):
    return sum(int(x) for x in n)

A, B = input().split()
print(max(S(A), S(B)))

