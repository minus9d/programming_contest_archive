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
T = input()
if len(S) + 1 == len(T) and T.startswith(S):
    print("Yes")
else:
    print("No")

