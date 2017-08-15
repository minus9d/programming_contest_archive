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

R, G, B = input().split()
if int(R + G + B) % 4 == 0:
    ans = 'YES'
else:
    ans = 'NO'
print(ans)

