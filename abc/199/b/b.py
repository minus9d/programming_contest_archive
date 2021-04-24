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
Bs = list(map(int, input().split()))
mn = max(As)
mx = min(Bs)
print(max(0, mx - mn + 1))

