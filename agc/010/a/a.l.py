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

N = int(input())
As = list(map(int, input().split()))

odd = 0
for a in As:
    odd += a % 2
if odd % 2:
    print('NO')
else:
    print('YES')

