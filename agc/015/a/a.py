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

N, A, B = map(int, input().split())
if N == 1:
    if A != B:
        print(0)
    else:
        print(1)
else:
    if A > B:
        print(0)
    else:
        mn = A * (N - 1) + B
        mx = A + B * (N - 1)
        print(mx - mn + 1)

