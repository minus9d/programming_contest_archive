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

A, B, C = map(int, input().split())
s = set([A, B, C])
if len(s) == 2:
    print('Yes')
else:
    print('No')

