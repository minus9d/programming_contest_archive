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

N, K = map(int, input().split())
S = input()
chset = set(S)
chlist = sorted(list(chset))

if K > N:
    ans = S[:] + chlist[0] * (K - N)
    print(ans)
else:    
    ans = list(S[:K])
    i = len(ans) - 1
    while True:
        ch = ans[i]
        ch_order = chlist.index(ch)
        if ch_order == len(chlist) - 1:
            ans[i] = chlist[0]
            i -= 1
        else:
            ans[i] = chlist[ch_order + 1]
            break
    print(''.join(ans))

