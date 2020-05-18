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

K = int(input())
S = input()
if len(S) <= K:
    print(S)
else:
    print(S[:K] + "...")

