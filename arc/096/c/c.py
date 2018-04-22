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

A, B, C, X, Y = map(int, input().split())

ans = int(1e100)
ab_num = 0

while ab_num // 2 <= max(X, Y):
    money = ab_num * C
    money += max(0, (X - ab_num // 2)) * A
    money += max(0, (Y - ab_num // 2)) * B
    ans = min(ans, money)
    ab_num += 2

print(ans)    
