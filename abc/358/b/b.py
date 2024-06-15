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


N, A  = map(int, input().split())
T = list(map(int, input().split()))

end_time = 0
for t in T:
    if t < end_time:
        end_time += A
    else:
        end_time = t + A
    print(end_time)


    
    

