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

A, B = map(int, input().split())
mx = 2 * A + 100
print(max(mx - B, 0))

