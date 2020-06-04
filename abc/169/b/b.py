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

if 0 in As:
    print(0)
else:
    ans = 1
    for a in As:
        ans *= a
        if ans > 10 ** 18:
            break
    if ans > 10 ** 18:
        print(-1)
    else:
        print(ans)


