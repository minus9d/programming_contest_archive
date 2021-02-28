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

K = int(input())
S = input()
T = input()

card_num = [0] + [K] * 9
for ch in S + T:
    if ch != '#':
        card_num[int(ch)] -= 1

def calc_score(S, n1):
    s = [0] * 10
    for ch in S[:4]:
        s[int(ch)] += 1
    s[n1] += 1

    score = 0
    for ch in range(1, 10):
        score += ch * 10 ** s[ch]

    return score
        

taka = 0
for n1 in range(1, 10):
    for n2 in range(1, 10):
        if n1 == n2:
            if card_num[n1] < 2:
                continue
            comb = card_num[n1] * (card_num[n1] - 1)
        else:
            if card_num[n1] < 1 or card_num[n2] < 1:
                continue
            comb = card_num[n1] * card_num[n2]

        s1 = calc_score(S, n1)
        s2 = calc_score(T, n2)
        # print("n1, n2, s1, s2 = ", n1, n2, s1, s2)
        if s1 > s2:
            taka += comb

s = K * 9 - 8
t = s * (s - 1)

ans = taka / t

print("{:.10f}".format(ans))

