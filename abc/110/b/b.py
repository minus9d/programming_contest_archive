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

N, M, X, Y = map(int, input().split())
Xs = list(map(int, input().split()))
Ys = list(map(int, input().split()))
Xs.append(X)
Ys.append(Y)
if max(Xs) < min(Ys):
    print('No War')
else:
    print('War')
