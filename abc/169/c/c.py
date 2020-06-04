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

A, B = input().split()
A = int(A)
B100 = int(B.replace(".", ""))

ans100 = A * B100
print(ans100 // 100)



