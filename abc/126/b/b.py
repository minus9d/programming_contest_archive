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


def is_yymm(S):
    return 1 <= int(S[2:]) <= 12

def is_mmyy(S):
    return 1 <= int(S[:2]) <= 12

S = input()
if is_yymm(S):
    if is_mmyy(S):
        print('AMBIGUOUS')
    else:
        print('YYMM')
elif is_mmyy(S):
    if is_yymm(S):
        print('AMBIGUOUS')
    else:
        print('MMYY')
else:
    print('NA')

