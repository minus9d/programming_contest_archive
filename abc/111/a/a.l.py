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

S = input()
T = ''
for ch in S:
    if ch == '1':
        T += '9'
    else:
        T += '1'
print(T)

        

