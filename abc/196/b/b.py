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

S = input()
if '.' in S:
    items = S.split('.')
    print(items[0])
else:
    print(S)



