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

A, B, C, K = map(int, input().split())

n1 = min(A, K)
ans = n1
K -= n1

n2 = min(B, K)
K -= n2

n3 = min(C, K)
ans -= n3

print(ans)



