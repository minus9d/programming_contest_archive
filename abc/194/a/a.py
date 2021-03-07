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

A, B = map(int, input().split())
A = A + B

if A >= 15 and B >= 8:
    print(1)
elif A >= 10 and B >= 3:
    print(2)
elif A >= 3:
    print(3)
else:
    print(4)

