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
As = list(map(int, input().split()))

for k in range(K, N):
    if As[k] > As[k - K]:
        print('Yes')
    else:
        print('No')
