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


a, b = map(int, input().split())

def func(a, b):
    if abs(a - b) != 1:
        return False

    mn = min(a, b)
    if mn in [3, 6]:
        return False
    
    return True

if func(a, b):
    print('Yes')
else:
    print('No')
