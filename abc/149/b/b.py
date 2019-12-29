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

A ,B, K = map(int, input().split())

x = min(A, K)
A -= x
K -= x

x = min(B, K)
B -= x

print(A, B)

