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
D, X = map(int, input().split())
ans = X
for n in range(N):
    a = int(input())
    ans += 1 + (D - 1) // a
print(ans)

