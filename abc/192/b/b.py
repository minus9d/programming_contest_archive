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

S = input()
odd = S[0::2]
even = S[1::2]

if odd == odd.lower() and even == even.upper():
    print('Yes')
else:
    print('No')

