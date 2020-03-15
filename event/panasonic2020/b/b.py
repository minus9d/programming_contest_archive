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

H, W = map(int, input().split())

# corner!!!
if H == 1 or W == 1:
    print(1)
else:
    if H % 2 == 1:
        ans = (H // 2) * W + (W + 1) // 2
    else:a
        ans = (H // 2) * W
    print(ans)
