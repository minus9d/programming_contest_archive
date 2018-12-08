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
As = []
for n in range(N):
    As.append(int(input()))
As.sort()
ans = sum(As)
ans -= As[-1] // 2
print(ans)
