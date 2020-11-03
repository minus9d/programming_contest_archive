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

N, D = map(int, input().split())
ans = 0
for n in range(N):
    x, y = map(int, input().split())
    ans += x ** 2 + y ** 2 <= D ** 2
print(ans)


