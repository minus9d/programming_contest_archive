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

num = 1
ok = 0
for a in As:
    if a == num:
        num += 1
        ok += 1

if ok == 0:
    print(-1)
else:
    print(N - ok)


