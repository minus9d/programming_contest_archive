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

S = input()
T = input()
ans = 0
for s, t in zip(S, T):
    ans += s != t
print(ans)
