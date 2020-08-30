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

mx = None
ans = 0
for a in As:
    if mx is None:
        mx = a
    else:
        if a >= mx:
            mx = a
        else:
            ans += mx - a
print(ans)

            

