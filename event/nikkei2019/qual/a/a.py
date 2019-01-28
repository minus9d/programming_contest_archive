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

N, A, B = map(int, input().split())
mx = min(A, B)
mn = max(A + B - N, 0)
print(mx, mn)
 
