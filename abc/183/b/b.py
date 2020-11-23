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

Sx, Sy, Gx, Gy = map(int, input().split())
Sy = -Sy

tmp = (Gy - Sy) * Sx - Sy * (Gx - Sx)
ans = tmp / (Gy - Sy)

print("{:.12f}".format(ans))

