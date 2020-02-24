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

N, R = map(int, input().split())
if N >= 10:
    print(R)
else:
    print(R + 100 * (10 - N))

