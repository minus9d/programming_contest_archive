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
s = sum(int(x) for x in S)
if s % 9 == 0:
    print('Yes')
else:
    print('No')


