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

A, B, C = map(int, input().split())
c = Counter([A, B, C])
if len(c) == 3:
    print(0)
elif len(c) == 1:
    for k, v in c.items():
        print(k)
else:
    for k, v in c.items():
        if v == 1:
            print(k)

    

