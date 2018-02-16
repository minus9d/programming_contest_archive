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

k = int(input())
if k <= 18:
    print('4' * k)
elif k <= 36:
    a = k - 18
    b = 18 - a
    print('8' * a + '4' * b)
else:
    print(-1)

