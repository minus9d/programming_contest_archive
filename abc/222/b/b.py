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


sys.setrecursionlimit(10 ** 9)


N, P = map(int, input().split())
As = list(map(int, input().split()))
print(sum(1 for a in As if a < P))
