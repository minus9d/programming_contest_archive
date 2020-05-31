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

def solve(N, As):
    if N == 0:
        if As[0] == 1:
            return 1
        else:
            return -1

    if As[0] != 0:
        return -1

    depth = N
    mx = 2 ** depth
    prev_leaf = None

    leaf_sum = sum(As)

    ans = 0
    curr = 0
    Vs = [None] * (N + 1)
    for n in range(N + 1):
        if n == 0:
            curr = 1
            ans += 1
        else:
            # 頂点を増やせるだけ増やす
            curr2 = min(curr * 2, leaf_sum)
            # 矛盾したら終わり
            if curr2 < As[n]:
                return -1
            # 頂点全部足す
            ans += curr2
            # 次に残れる頂点
            curr = curr2 - As[n]
            # 使った葉のぶんを引く
            leaf_sum -= As[n]

    return ans


def main():
    N = int(input())
    As = list(map(int, input().split()))
    print(solve(N, As))

    
main()
