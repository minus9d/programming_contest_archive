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

x1, y1, x2, y2 = map(int, input().split())

y3 = y2 + (x2 - x1)
x3 = x2 - (y2 - y1)
y4 = y3 + (x3 - x2)
x4 = x3 - (y3 - y2)
print(x3, y3, x4, y4)

