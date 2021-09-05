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


sys.setrecursionlimit(10 ** 9)


st = set(['ABC' , 'ARC' , 'AGC' , 'AHC'])
for n in range(3):
    s = input()
    st.remove(s)
print(*st)


