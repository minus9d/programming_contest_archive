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

N = int(input())
S = set(input().split())
if len(S) == 3:
    print("Three")
else:
    print("Four")
 
