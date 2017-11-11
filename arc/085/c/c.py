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

N, M = map(int, input().split())
time = 1900 * M + 100 * (N - M)
ans = time * (2 ** M)
print(ans)
