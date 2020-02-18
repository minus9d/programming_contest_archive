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

ok = True
for a in As:
    if a % 2 == 0:
        if a % 3 == 0 or a % 5 == 0:
            pass
        else:
            ok = False
if ok:
    print('APPROVED')
else:
    print('DENIED')

