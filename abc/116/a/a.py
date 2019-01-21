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

lengths = list(sorted(map(int, input().split())))
print(lengths[0] * lengths[1] // 2)

