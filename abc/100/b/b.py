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

D, N = map(int, input().split())
if N <= 99:
    print(N * (100 ** D))
else:
    print(101 * (100 ** D))
