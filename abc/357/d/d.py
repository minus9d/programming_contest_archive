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


def mod_pow(x, n, mod):
  res = 1
  while n > 0:
    if (n & 1):
       res = res * x % mod
    x = x * x % mod
    n >>= 1
  return res

def modInverse(x):
  return mod_pow(x, MOD-2, MOD)


def modDivision(p, q):
  return (p * modInverse(q)) % MOD


MOD = 998244353
N = int(input())
len_of_N = len(str(N))

val = ()
r = 10 ** len_of_N

val = (N % MOD) * (pow(r, N, MOD) - 1)
val %= MOD

ans = modDivision(val, r - 1)
print(ans)
