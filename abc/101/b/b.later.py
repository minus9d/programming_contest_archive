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
SN = sum(int(x) for x in str(N))
if N % SN:
    print("No")
else:
    print("Yes")

