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

X = int(input())
if X % 100 == 0:
    print(100)
else:
    print(100 - (X % 100))


