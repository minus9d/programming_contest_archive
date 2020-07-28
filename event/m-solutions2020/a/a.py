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

X = int(input())
if X < 600:
    print(8)
elif X < 800:
    print(7)
elif X < 1000:
    print(6)
elif X < 1200:
    print(5)
elif X < 1400:
    print(4)
elif X < 1600:
    print(3)
elif X < 1800:
    print(2)
else:
    print(1)

