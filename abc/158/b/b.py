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

N, A, B = map(int, input().split())

num = N // (A + B)
blue = num * A
blue += min(A, N - (A + B) * num)
print(blue)

