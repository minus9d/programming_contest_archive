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


N = input()
if len(N) == 1:
    print('Yes')
else:
    ok = True
    for i in range(len(N) - 1):
        n1 = int(N[i])
        n2 = int(N[i+1])
        if n1 <= n2:
            ok = False
    if ok:
        print('Yes')
    else:
        print('No')
