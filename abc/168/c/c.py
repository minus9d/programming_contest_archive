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

A, B, H, M = map(int, input().split())

short_rate = (H * 60 + M) / 720
long_rate = M / 60

def to_arg(rate):
    return - 2 * math.pi * rate

short = (0 + A * 1j)
short *= (math.cos(to_arg(short_rate)) + 1j * math.sin(to_arg(short_rate)))

long = (0 + B * 1j)
long *= (math.cos(to_arg(long_rate)) + 1j * math.sin(to_arg(long_rate)))

print("{:.20f}".format(abs(long - short)))


