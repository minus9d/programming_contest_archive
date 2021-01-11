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

X, Y = map(int, input().split())
mn = min(X, Y)
mx = max(X, Y)
if mn + 3 > mx:
    print('Yes')
else:
    print('No')

