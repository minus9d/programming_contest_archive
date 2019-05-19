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

N, K = map(int, input().split())
S = list(input())

S[K - 1] = S[K - 1].lower()

print("".join(S))


