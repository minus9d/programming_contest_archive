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
As = map(int, input().split())

ans = 0
for a in As:
    while a % 2 == 0:
        a //= 2
        ans += 1
print(ans)

