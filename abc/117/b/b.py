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

N = int(input())
Ls = sorted(map(int, input().split()))
if Ls[-1] < sum(Ls) - Ls[-1]:
    print('Yes')
else:
    print('No')
    

