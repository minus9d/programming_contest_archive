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


N = int(input())
As = list(map(int, input().split()))
As.sort()

if As == list(range(1, N + 1)):
    print('Yes')
else:
    print('No')


