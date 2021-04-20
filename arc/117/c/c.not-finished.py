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

def solve_fast(s):
    ch1 = s[0]
    for ch2 in s[1:]:
        if ch1 == ch2:
            new_ch = ch1
        elif set([ch1, ch2]) == set('RW'):
            new_ch = 'B'
        elif set([ch1, ch2]) == set('BW'):
            new_ch = 'R'
        elif set([ch1, ch2]) == set('RB'):
            new_ch = 'W'

        ch1 = new_ch

    return ch1

def solve_slow(s):
    inter = []
    while len(s) > 1:
        inter.append(s)
        new_s = []
        for i in range(len(s) - 1):
            ch1 = s[i]
            ch2 = s[i + 1]
            if ch1 == ch2:
                new_s.append(ch1)
            elif set([ch1, ch2]) == set('RW'):
                new_s.append('B')
            elif set([ch1, ch2]) == set('BW'):
                new_s.append('R')
            elif set([ch1, ch2]) == set('RB'):
                new_s.append('W')
        s = new_s
    inter.append(s)
    print()

    offset = 0
    for line in inter:
        print(' ' * offset + ' '.join(line))
        offset += 1

    return s[0]


s = list('WBBWBRWWW')
print(s, solve_slow(s))
for ch in 'WBR':
    s2 = s[:]
    s2.append(ch)
    res = solve_slow(s2)
    print(s2, res)

for repeat in range(1, 10):
    res2comb = defaultdict(list)

    ok = 0
    ng = 0
    for comb in product('BRW', repeat=repeat):
        res = solve_slow(comb)
        # print(''.join(comb), res)
        res2comb[res].append(comb)

        # res2 = solve_fast(comb)
        # if res != res2:
        #     # print("error!")
        #     # print("comb = ", comb)
        #     # print("res, res2 = ", res, res2)
        #     # sys.exit(0)
        #     # print()
        #     # print("ng: ", "".join(comb))
        #     # ng += 1
        # else:
        #     # print("ok")
        #     # print("ok: ", "".join(comb))
        #     ok += 1
    # print("ok, ng = ", ok, ng)

    for res, combs in res2comb.items():
        print(res)
        for comb in combs:
            print("  ", ''.join(comb))
        print()
    print()




# N = int(input())

