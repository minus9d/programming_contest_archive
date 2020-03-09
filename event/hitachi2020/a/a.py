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
ok = True
while S:
    if S.startswith("hi"):
        S = S[2:]
    else:
        ok = False
        break
if ok:
    print("Yes")
else:
    print("No")

