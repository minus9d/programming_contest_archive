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

N = int(input())
ans = 0
while N > 0:
    if N >= 6:
        ans += 1
        N -= 3
    elif N >= 3:
        ans += 1
        N = 0
    else:
        N = 0
print(ans)

 
