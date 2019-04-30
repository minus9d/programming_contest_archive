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

N, X, Y = map(int, input().split())
As = list(map(int, input().split()))
As.sort()
As.reverse()

X2 = X + sum(As[0::2])
Y2 = Y + sum(As[1::2])
if X2 > Y2:
    print('Takahashi')
elif X2 == Y2:
    print('Draw')
else:
    print('Aoki')


