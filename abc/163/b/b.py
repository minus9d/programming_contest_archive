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

N, M = map(int, input().split())
As = list(map(int, input().split()))
s = sum(As)
if s > N:
    print(-1)
else:
    print(N - s)


