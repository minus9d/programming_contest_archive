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

C, D = map(int, input().split())

ans = 0
s = 140
e = 170
while True:
    if C >= e:
        pass
    elif D <= s:
        break
    else:
        mx = min(e, D)
        mn = max(s, C)
        ans += mx - mn
    s *= 2
    e *= 2
print(ans)
        
        
