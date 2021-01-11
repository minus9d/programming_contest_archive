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

import numpy as np

N = int(input())
As = np.array(list(map(int, input().split())))

mx_idx = np.argmax(As)
# print(mx_idx)

if mx_idx < 2 ** (N - 1):
    print(np.argmax(As[(2 ** (N - 1)):]) + (2 ** (N - 1)) + 1)
else:
    print(np.argmax(As[:(2 ** (N - 1))]) + 1)



