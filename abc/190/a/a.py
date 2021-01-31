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

A, B, C = map(int, input().split())
taka = None
if C == 0:
    if A <= B:
        taka = False
    else:
        taka = True
else:
    if B <= A:
        taka = True
    else:
        taka = False
if taka:
    print('Takahashi')
else:
    print('Aoki')

