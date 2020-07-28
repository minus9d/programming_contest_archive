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

R, G, B = map(int, input().split())
K = int(input())

for k in range(K):
    if G <= R:
        G *= 2
    elif B <= G:
        B *= 2
    else:
        B *= 2

if B > G > R:
    print("Yes")
else:
    print("No")


