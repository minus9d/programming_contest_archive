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


sys.setrecursionlimit(10 ** 9)



def solve(A, B, C):
    if C >= 2:
        if C % 2 == 1:
            C = 3
        else:
            C = 2

    num1 = A ** C
    num2 = B ** C
    
    if num1 < num2:
        return '<'
    elif num1 == num2:
        return '='
    else:
        return '>'

A, B, C  = map(int, input().split())
print(solve(A, B, C))    
