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

S, T = input().split()
A, B = map(int, input().split())
U = input()
if U == S:
    print(A - 1, B)
else:
    print(A, B - 1)

