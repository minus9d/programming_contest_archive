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

n, L, R = map(int, input().split())
ret = []
As = map(int, input().split())
for a in As:
    ret.append(max(L, min(R, a)))
print(*ret)
