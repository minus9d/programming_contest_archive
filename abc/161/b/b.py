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

N, M = map(int, input().split())
As = list(map(int, input().split()))
s = sum(As)
As.sort(reverse=True)

ok = True
for m in range(M):
    if As[m] * 4 * M >= s:
        pass
    else:
        ok = False
if ok:
    print('Yes')
else:
    print('No')

