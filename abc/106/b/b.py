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

N = int(input())
prev = None
ok = True
seen = set()
for n in range(N):
    w = input()
    if prev is None:
        prev = w
    else:
        if prev[-1] != w[0]:
            ok = False
    if w in seen:
        ok = False
    seen.add(w)
    prev = w
if ok:
    print('Yes')
else:
    print('No')
    
 
