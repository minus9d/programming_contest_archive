#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import array
from bisect import *
from collections import *
import fractions
import heapq 
from itertools import *
import math
import re
import string

_ = input()
S = input()
stack = 0
made = ''
for ch in S:
    # print("ch, stack = ", ch, stack)
    if ch == '(':
        stack += 1
        made += '('
    elif ch == ')':
        if stack == 0:
            made = '(' + made + ')'
        else:
            made += ')'
            stack -= 1
made += ')' * stack
print(made)
            
