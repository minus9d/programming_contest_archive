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

D, T, S = map(int, input().split())
if T * S >= D:
    print('Yes')
else:
    print('No')
