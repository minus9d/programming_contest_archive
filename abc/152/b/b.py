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

a, b = input().split()
a2 = a * int(b)
b2 = b * int(a)
print(min(a2, b2))

