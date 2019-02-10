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

K, A, B = map(int, input().split())

bis = 1
if A - 1 <= K:
    K -= (A - 1)
    bis += A - 1

if B - A > 2:
    print(bis + (K // 2) * (B - A) + (K % 2))
else:
    print(bis + K)
