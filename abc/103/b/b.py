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

for i in range(len(S)):
    S2 = S[i:] + S[:i]
    if S2 == T:
        print("Yes")
        sys.exit(0)
print("No")

