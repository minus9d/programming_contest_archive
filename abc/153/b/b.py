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

H, N = map(int, input().split())
As = list(map(int, input().split()))
s = sum(As)
if s >= H:
    print("Yes")
else:
    print("No")


