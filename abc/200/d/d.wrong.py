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
As = list(map(int, input().split()))

def print_ans(arr1, arr2):
    def print_line(arr):
        arr = [len(arr)] + list(arr)
        print(*arr)
    print("Yes")
    print_line(arr1)
    print_line(arr2)
    

val_to_arr = {}
for i, a in enumerate(As):
    nxt = {}
    a %= 200

    # (iii) add one
    if a in val_to_arr:
        print_ans(val_to_arr[a], tuple([i + 1]))
        sys.exit(0)
    nxt[a] = tuple([i + 1])

    for val, arr in val_to_arr.items():

        # (i) add
        arr2 = tuple(list(arr) + [i + 1])

        val2 = (val + a) % 200
        if val2 in val_to_arr:
            # 空はダメ
            if not val_to_arr[val2]:
                continue
            print_ans(val_to_arr[val2], arr2)
            sys.exit(0)
        nxt[val2] = arr2

        # (ii) no add
        nxt[val] = arr

    val_to_arr = nxt
    # print("now: ", val_to_arr)

print("No")

        
    

