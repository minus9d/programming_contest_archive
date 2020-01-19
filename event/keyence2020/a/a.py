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

H = int(input())
W = int(input())
N = int(input())

a = max(H, W)
print((N + a - 1) // a)

