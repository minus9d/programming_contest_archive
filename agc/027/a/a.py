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

N, x = map(int, input().split())
As = list(map(int, input().split()))
As.sort()

ans = 0
for i, a in enumerate(As):
    if i != N - 1:
        if x >= a:
            ans += 1
            x -= a
    else:
        if x == a:
            ans += 1
            
print(ans)

