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


sys.setrecursionlimit(10 ** 9)


H, W  = map(int, input().split())
ans = 0
for h in range(H):
    ans += input().count('#')
print(ans)
