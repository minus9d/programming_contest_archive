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

As = list(map(int, input().split()))
for i in range(5):
    if As[i] == 0:
        print(i + 1)

