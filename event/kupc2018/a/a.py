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
Ss = map(int, input().split())
As = map(int, input().split())

print(max(s * a for s, a in zip(Ss, As)))

