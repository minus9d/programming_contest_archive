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


def print2(*args, **kwargs):
    print(*args, **kwargs)
    sys.stdout.flush()

N, K = map(int, input().split())
if K == 1:
    ans = []
    for n in range(N):
        print2(f"? {n + 1}")
        res = int(input())
        ans.append(res)
    print2("!", end=" ")
    print2(*ans)
else:
    if K * 2 < N:
        query = [i + 1 for i in range(K)]
        print(query)

        buffer = [None] * N

        while True:
            print2(f"?", end=" ")
            print2(*query)

            res = int(input())
            
            
            

            query[-1] += 1
            if query[-1] > N:
                break

    else:
        print("...")


            

