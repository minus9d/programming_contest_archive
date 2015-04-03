#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from functools import lru_cache

def getBit(num, i):
  return (num >> i) & 1  # Returns the i-th bit value of num.


# lessMフラグがTrueなら、次のbitのlessMはtrue
# Mのi番目のbitが1なら、次のbitのlessMはtrue
@lru_cache(maxsize = None)
def count(i, lessM, M):
  if i == -1:  # The base case.
    return lessM  # only count if it is strictly less than M.

  maxM = lessM or getBit(M, i) == 1
#  print("maxM =", maxM);

  res = count(i - 1, maxM, M)  # Value 0 is always feasible. See (1) below.

  if maxM: # Value 1 is feasible if maxM is true. See (2) below.
    res += count(i - 1, lessM, M)  # See (3) below.

  return res

# Prints how many non-negative numbers that are less than 123456789
print(count(31, False, 123456789))
