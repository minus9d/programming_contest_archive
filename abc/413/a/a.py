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


N, M  = map(int, input().split())
A = list(map(int, input().split()))
if sum(A) <= M:
    print('Yes')
else:
    print('No')


