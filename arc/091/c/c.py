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

H, W = map(int, input().split())
if H > W:
    H, W = W, H
ans = None
if H == 1:
    if W == 1:
        ans = 1
    else:
        ans = W - 2
elif H == 2:
    ans = 0
else:
    ans = (H - 2) * (W - 2)
print(ans)

