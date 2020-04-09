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

N, K = map(int, input().split())
N -= (N // K) * K

tmp1 = N
tmp2 = abs(K - N)
print(min(tmp1, tmp2))


