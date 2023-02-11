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


s = input()
s = s.replace('0', '2')
s = s.replace('1', '0')
s = s.replace('2', '1')
print(s)
