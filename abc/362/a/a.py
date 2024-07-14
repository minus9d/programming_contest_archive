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


R, G, B  = map(int, input().split())
C = input()[0]
if C == 'R':
    print(min(G, B))
elif C == 'G':
    print(min(R, B))
elif C == 'B':
    print(min(R, G))

