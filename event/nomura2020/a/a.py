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

H1, M1, H2, M2, K = map(int, input().split())

dur = (H2 - H1) * 60 + M2 - M1
print(max(0, dur - K))

